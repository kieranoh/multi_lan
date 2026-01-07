/**
 * 제공된 이메일 주소가 유효한지 확인합니다.
 * RFC 5322 표준을 기반으로 한 포괄적인 이메일 유효성 검사 함수입니다.
 * 
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고 
 *                                두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 정규식 패턴들
    const patterns = {
        // 기본적인 이메일 형식 검증 (가장 일반적인 패턴)
        basic: /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/,
        
        // 국제화 도메인 이름(IDN)을 지원하는 확장 패턴
        extended: /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/,
        
        // RFC 5322 표준을 준수하는 포괄적인 패턴
        rfc5322: /^(?:[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-zA-Z0-9-]*[a-zA-Z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])$/,
        
        // 다중 하위 도메인을 지원하는 패턴 (abc.123@def.ghi.com.uk 형태)
        multiSubdomain: /^[a-zA-Z0-9._%+-]+@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}(?:\.[a-zA-Z]{2,})*$/,
        
        // 국제화 이메일 주소(UTF-8 문자 포함)를 지원하는 패턴
        unicode: /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/
    };
    
    // 입력값이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'invalid_input_type'];
    }
    
    // 빈 문자열 체크
    if (email.trim() === '') {
        return [false, 'empty_string'];
    }
    
    // 이메일 길이 체크 (RFC 5321 기준: 로컬파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length > 320) {
        return [false, 'too_long'];
    }
    
    // @ 기호가 정확히 하나만 있는지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, 'invalid_at_symbol_count'];
    }
    
    // @ 기호 위치 확인 (처음이나 끝에 올 수 없음)
    if (email.startsWith('@') || email.endsWith('@')) {
        return [false, 'invalid_at_position'];
    }
    
    // 로컬파트와 도메인 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // 로컬파트 길이 체크 (RFC 기준: 최대 64자)
    if (localPart.length > 64) {
        return [false, 'local_part_too_long'];
    }
    
    // 도메인 길이 체크 (RFC 기준: 최대 255자)
    if (domainPart.length > 255) {
        return [false, 'domain_too_long'];
    }
    
    // 도메인에 점(.)이 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, 'no_dot_in_domain'];
    }
    
    // 도메인의 마지막 부분(최상위 도메인)이 너무 짧거나 긴지 확인
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, 'tld_too_short'];
    }
    
    // 연속된 점(..)이 있는지 확인
    if (email.includes('..')) {
        return [false, 'consecutive_dots'];
    }
    
    // 점으로 시작하거나 끝나는 도메인 부분이 있는지 확인
    for (const part of domainParts) {
        if (part.startsWith('.') || part.endsWith('.') || part === '') {
            return [false, 'invalid_domain_part'];
        }
    }
    
    // 점으로 시작하거나 끝나는 로컬파트 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'invalid_local_part'];
    }
    
    // 다양한 패턴으로 검증 시도 (가장 엄격한 것부터 점진적으로 검증)
    if (patterns.rfc5322.test(email)) {
        return [true, 'rfc5322'];
    }
    
    if (patterns.multiSubdomain.test(email)) {
        return [true, 'multi_subdomain'];
    }
    
    if (patterns.unicode.test(email)) {
        return [true, 'unicode'];
    }
    
    if (patterns.extended.test(email)) {
        return [true, 'extended'];
    }
    
    if (patterns.basic.test(email)) {
        return [true, 'basic'];
    }
    
    // 모든 검증 실패 시
    return [false, 'no_pattern_match'];
};

// 함수를 모듈로 내보내기 (Node.js 환경용)
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { checkEmail };
}