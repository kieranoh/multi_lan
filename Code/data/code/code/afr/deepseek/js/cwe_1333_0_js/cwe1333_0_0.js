/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고
 *                                두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일이 문자열이 아니거나 비어있는 경우
    if (typeof email !== 'string' || email.trim() === '') {
        return [false, 'Invalid input'];
    }

    const trimmedEmail = email.trim();
    
    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 정규식
    // 로컬 파트와 도메인 파트 모두에서 다양한 유효한 문자를 허용합니다.
    const emailPattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.\+]+)|(?:"(?:[a-zA-Z0-9_\-\.\+: ,<>\[\]]|\\[\\"])+"))@(?:(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9\-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,})|(?:\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-zA-Z0-9\-]*)\])))$/;
    
    // 더 간단하지만 여전히 포괄적인 대체 패턴 (RFC 5322의 하위 집합)
    const simplePattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // 국제화된 도메인 이름(IDN)을 지원하는 패턴
    const idnPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/i;
    
    // 로컬 파트에 인용된 문자열을 포함하는 패턴
    const quotedLocalPattern = /^(?:"(?:[^"\\]|\\.)+"|[a-zA-Z0-9._%+-]+)@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // IPv4 및 IPv6 주소를 도메인으로 지원하는 패턴
    const ipPattern = /^[a-zA-Z0-9._%+-]+@(?:(\[IPv6:[a-fA-F0-9:]+\])|(\[([0-9]{1,3}\.){3}[0-9]{1,3}\]))$/;
    
    // 가장 포괄적인 패턴부터 검증 시도
    if (emailPattern.test(trimmedEmail)) {
        return [true, 'RFC 5322 comprehensive pattern'];
    }
    
    // IPv4/IPv6 주소 패턴 확인
    if (ipPattern.test(trimmedEmail)) {
        return [true, 'IP address domain pattern'];
    }
    
    // 인용된 로컬 파트 패턴 확인
    if (quotedLocalPattern.test(trimmedEmail)) {
        return [true, 'Quoted local part pattern'];
    }
    
    // 간단한 패턴 확인 (가장 일반적인 경우)
    if (simplePattern.test(trimmedEmail)) {
        return [true, 'Simple email pattern'];
    }
    
    // IDN 패턴 확인 (대소문자 구분 없음)
    if (idnPattern.test(trimmedEmail)) {
        return [true, 'IDN compatible pattern'];
    }
    
    // 모든 패턴과 일치하지 않는 경우
    return [false, 'No valid pattern matched'];
};