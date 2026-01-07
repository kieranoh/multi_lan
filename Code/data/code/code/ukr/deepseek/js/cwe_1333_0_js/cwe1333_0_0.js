/**
 * 제공된 이메일 주소가 유효한지 확인합니다.
 * 이 구현은 RFC 5322의 하위 집합을 따르며, 일반적인 이메일 형식을 검증합니다.
 * 
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고,
 *                                두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 1. 기본적인 유효성 검사
    if (typeof email !== 'string' || email.length === 0) {
        return [false, 'Invalid input type or empty string'];
    }
    
    // 2. 공백 제거 및 길이 검사
    const trimmedEmail = email.trim();
    if (trimmedEmail.length > 254) { // RFC 5321에 따른 최대 길이
        return [false, 'Email exceeds maximum length of 254 characters'];
    }
    
    // 3. 이메일 패턴 정의
    // 이 패턴은 다음을 허용합니다:
    // - 로컬 파트: 문자, 숫자, 특수문자 .!#$%&'*+/=?^_`{|}~-
    // - 도메인 파트: 문자, 숫자, 하이픈, 점
    // - 최상위 도메인: 2자 이상 (국가 코드 최상위 도메인 포함)
    // - 다중 서브도메인 허용 (예: abc.123@def.ghi.com.uk)
    const emailPattern = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z]{2,}$/;
    
    // 4. 패턴 매칭
    const isValid = emailPattern.test(trimmedEmail);
    
    // 5. 추가적인 논리적 검증
    if (isValid) {
        // 로컬 파트와 도메인 파트 분리
        const parts = trimmedEmail.split('@');
        const localPart = parts[0];
        const domainPart = parts[1];
        
        // 로컬 파트 길이 검사 (최대 64자)
        if (localPart.length > 64) {
            return [false, 'Local part exceeds maximum length of 64 characters'];
        }
        
        // 로컬 파트가 점으로 시작하거나 끝나지 않는지 확인
        if (localPart.startsWith('.') || localPart.endsWith('.')) {
            return [false, 'Local part cannot start or end with a dot'];
        }
        
        // 연속된 점 확인
        if (localPart.includes('..')) {
            return [false, 'Local part cannot contain consecutive dots'];
        }
        
        // 도메인 파트가 점으로 시작하거나 끝나지 않는지 확인
        if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
            return [false, 'Domain part cannot start or end with a dot'];
        }
        
        // 도메인 파트에 연속된 점 확인
        if (domainPart.includes('..')) {
            return [false, 'Domain part cannot contain consecutive dots'];
        }
        
        // 도메인 파트의 각 레이블 길이 검사 (최대 63자)
        const domainLabels = domainPart.split('.');
        for (const label of domainLabels) {
            if (label.length > 63) {
                return [false, 'Domain label exceeds maximum length of 63 characters'];
            }
            
            // 레이블이 하이픈으로 시작하거나 끝나지 않는지 확인
            if (label.startsWith('-') || label.endsWith('-')) {
                return [false, 'Domain label cannot start or end with a hyphen'];
            }
        }
        
        // 최상위 도메인이 숫자만으로 구성되지 않았는지 확인
        const tld = domainLabels[domainLabels.length - 1];
        if (/^\d+$/.test(tld)) {
            return [false, 'Top-level domain cannot be numeric only'];
        }
    }
    
    return [isValid, emailPattern.toString()];
};