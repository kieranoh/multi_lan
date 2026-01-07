/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고 
 * 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // RFC 5322 호환 이메일 검증을 위한 패턴
    // 이 패턴은 다음과 같은 이메일 형식을 지원합니다:
    // - 로컬 파트: 문자, 숫자, 특수문자 . ! # $ % & ' * + / = ? ^ _ ` { | } ~ -
    // - 도메인 파트: 문자, 숫자, 하이픈, 점
    // - 최상위 도메인: 2자 이상
    // - 다중 서브도메인 지원 (예: abc.123@def.ghi.com.uk)
    const emailPattern = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z]{2,}$/;
    
    // 추가 검증: 이메일 길이 확인 (RFC 5321 기준)
    // 로컬 파트: 최대 64자, 도메인 파트: 최대 255자, 전체: 최대 254자
    if (email.length > 254) {
        return [false, "email_too_long"];
    }
    
    const atIndex = email.indexOf('@');
    if (atIndex === -1) {
        return [false, "no_at_symbol"];
    }
    
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    if (localPart.length === 0 || localPart.length > 64) {
        return [false, "invalid_local_part_length"];
    }
    
    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, "invalid_domain_length"];
    }
    
    // 로컬 파트의 연속된 점 확인
    if (localPart.includes('..')) {
        return [false, "consecutive_dots_in_local"];
    }
    
    // 로컬 파트의 시작 또는 끝에 점 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, "dot_at_edge_of_local"];
    }
    
    // 도메인 파트의 연속된 점 확인
    if (domainPart.includes('..')) {
        return [false, "consecutive_dots_in_domain"];
    }
    
    // 도메인 파트의 시작 또는 끝에 점 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, "dot_at_edge_of_domain"];
    }
    
    // 도메인 파트에 유효한 문자가 있는지 확인
    const domainPattern = /^[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*\.[a-zA-Z]{2,}$/;
    if (!domainPattern.test(domainPart)) {
        return [false, "invalid_domain_format"];
    }
    
    // 최종 이메일 패턴 검증
    const isValid = emailPattern.test(email);
    return [isValid, isValid ? "valid_email_pattern" : "invalid_email_pattern"];
};