/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고,
 *                                두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // RFC 5322 호환 이메일 검증 정규식 (단순화된 버전)
    const pattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 기본적인 길이 검사
    if (typeof email !== 'string' || email.length === 0 || email.length > 254) {
        return [false, pattern.toString()];
    }
    
    // 정규식 검사
    const isValid = pattern.test(email);
    
    // 추가 검증: 도메인 부분에 연속된 점이 없는지 확인
    if (isValid) {
        const domainPart = email.split('@')[1];
        if (domainPart.includes('..') || domainPart.startsWith('.') || domainPart.endsWith('.')) {
            return [false, pattern.toString()];
        }
        
        // 로컬 부분 검증 (로컬 부분에 연속된 점이 없는지 확인)
        const localPart = email.split('@')[0];
        if (localPart.includes('..') || localPart.startsWith('.') || localPart.endsWith('.')) {
            return [false, pattern.toString()];
        }
        
        // 최상위 도메인이 최소 2자 이상인지 확인 (예: .com, .co.uk)
        const domainParts = domainPart.split('.');
        const lastPart = domainParts[domainParts.length - 1];
        if (lastPart.length < 2) {
            return [false, pattern.toString()];
        }
    }
    
    return [isValid, pattern.toString()];
};