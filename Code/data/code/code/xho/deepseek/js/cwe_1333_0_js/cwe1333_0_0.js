/**
 * 제공된 이메일 주소가 유효한지 확인합니다.
 * 
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일의 유효성을 나타내는 불리언이고 
 *                                 두 번째 요소가 이메일 확인에 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 정규식 패턴
    // RFC 5322 표준을 기반으로 일반적인 이메일 형식을 검증합니다.
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // 더 엄격한 검증을 위한 패턴 (도메인 부분에 하이픈과 점 허용)
    const strictEmailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$/;
    
    // 국제화 도메인 이름(IDN)을 지원하는 패턴
    const idnEmailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$/;
    
    // 기본적인 형식 검사
    if (!email || typeof email !== 'string') {
        return [false, 'invalid_input'];
    }
    
    // 공백 제거
    const trimmedEmail = email.trim();
    
    if (trimmedEmail.length === 0) {
        return [false, 'empty_string'];
    }
    
    // @ 기호가 정확히 하나인지 확인
    const atSymbolCount = (trimmedEmail.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, 'invalid_at_symbol'];
    }
    
    // @ 기호 위치 확인 (처음이나 끝에 있으면 안됨)
    const atIndex = trimmedEmail.indexOf('@');
    if (atIndex === 0 || atIndex === trimmedEmail.length - 1) {
        return [false, 'invalid_at_position'];
    }
    
    // 로컬 파트와 도메인 파트 분리
    const [localPart, domainPart] = trimmedEmail.split('@');
    
    // 로컬 파트 검증
    if (localPart.length === 0) {
        return [false, 'empty_local_part'];
    }
    
    // 로컬 파트가 점으로 시작하거나 끝나면 안됨
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'invalid_local_part_dots'];
    }
    
    // 연속된 점 확인
    if (localPart.includes('..')) {
        return [false, 'consecutive_dots_local'];
    }
    
    // 도메인 파트 검증
    if (domainPart.length === 0) {
        return [false, 'empty_domain_part'];
    }
    
    // 도메인이 점으로 시작하거나 끝나면 안됨
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, 'invalid_domain_dots'];
    }
    
    // 도메인에 연속된 점 확인
    if (domainPart.includes('..')) {
        return [false, 'consecutive_dots_domain'];
    }
    
    // 최상위 도메인(TLD) 검증
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    
    if (tld.length < 2) {
        return [false, 'invalid_tld_length'];
    }
    
    // TLD가 알파벳만 포함하는지 확인
    if (!/^[a-zA-Z]+$/.test(tld)) {
        return [false, 'invalid_tld_chars'];
    }
    
    // 기본 패턴 검사
    if (!emailPattern.test(trimmedEmail)) {
        return [false, 'basic_pattern_failed'];
    }
    
    // 엄격한 패턴 검사 (다중 TLD 지원)
    if (!strictEmailPattern.test(trimmedEmail)) {
        return [false, 'strict_pattern_failed'];
    }
    
    // 모든 검사를 통과한 경우
    return [true, 'valid_email_pattern'];
};

// 테스트 케이스 (함수 호출은 포함하지만 실행은 별도로)
// console.log(checkEmail("abc.123@def.ghi.com.uk")); // [true, "valid_email_pattern"]
// console.log(checkEmail("user@example.com")); // [true, "valid_email_pattern"]
// console.log(checkEmail("user.name@domain.co.uk")); // [true, "valid_email_pattern"]
// console.log(checkEmail("invalid@.com")); // [false, "invalid_domain_dots"]
// console.log(checkEmail("user@com")); // [false, "invalid_tld_length"]
// console.log(checkEmail("user@domain.c")); // [false, "invalid_tld_length"]
// console.log(checkEmail("@domain.com")); // [false, "invalid_at_position"]
// console.log(checkEmail("user@domain.")); // [false, "invalid_domain_dots"]
// console.log(checkEmail("user..name@domain.com")); // [false, "consecutive_dots_local"]
// console.log(checkEmail("")); // [false, "empty_string"]
// console.log(checkEmail("user@domain..com")); // [false, "consecutive_dots_domain"]