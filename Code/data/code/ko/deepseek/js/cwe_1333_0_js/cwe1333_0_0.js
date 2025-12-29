/**
 * 제공된 이메일 주소가 유효한지 확인합니다.
 * 
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 
 * 두 번째 요소가 이메일 확인에 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // RFC 5322 호환 이메일 검증을 위한 정규식 패턴
    // 이 패턴은 대부분의 유효한 이메일 주소를 허용하면서도 일반적인 오류를 방지합니다
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 패턴 설명:
    // 1. ^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+ - 로컬 파트 시작 (하나 이상의 허용된 문자)
    // 2. (?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)* - 점으로 구분된 추가 로컬 파트 (선택적)
    // 3. @ - @ 기호
    // 4. (?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+ - 도메인 부분 (하나 이상의 서브도메인)
    // 5. [a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$ - 최상위 도메인
    
    // 기본 유효성 검사
    if (typeof email !== 'string' || email.length === 0) {
        return [false, emailPattern.toString()];
    }
    
    // 이메일 길이 검사 (RFC 5321 기준: 로컬 파트 최대 64자, 도메인 최대 255자)
    const atIndex = email.indexOf('@');
    if (atIndex === -1 || atIndex === 0 || atIndex === email.length - 1) {
        return [false, emailPattern.toString()];
    }
    
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    if (localPart.length > 64 || domainPart.length > 255 || email.length > 254) {
        return [false, emailPattern.toString()];
    }
    
    // 연속된 점 검사
    if (email.includes('..') || localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, emailPattern.toString()];
    }
    
    // 도메인 부분의 유효성 추가 검사
    const domainParts = domainPart.split('.');
    if (domainParts.length < 2) {
        return [false, emailPattern.toString()];
    }
    
    // 각 도메인 레이블 검사
    for (const label of domainParts) {
        if (label.length === 0 || label.length > 63) {
            return [false, emailPattern.toString()];
        }
        if (label.startsWith('-') || label.endsWith('-')) {
            return [false, emailPattern.toString()];
        }
        if (!/^[a-zA-Z0-9-]+$/.test(label)) {
            return [false, emailPattern.toString()];
        }
    }
    
    // 최상위 도메인 검사 (최소 2자 이상이어야 함)
    const topLevelDomain = domainParts[domainParts.length - 1];
    if (topLevelDomain.length < 2) {
        return [false, emailPattern.toString()];
    }
    
    // 정규식 패턴으로 최종 검증
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};