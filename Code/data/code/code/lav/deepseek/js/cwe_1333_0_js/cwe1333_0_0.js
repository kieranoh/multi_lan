/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고
 *                                두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // RFC 5322 호환 이메일 검증 정규식 (단순화된 버전)
    // 이 패턴은 대부분의 일반적인 이메일 형식을 지원하며, 국제화 도메인 이름(IDN)도 지원합니다.
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 추가 검증: 이메일 길이 확인 (RFC 5321 기준)
    if (email.length > 254) {
        return [false, "email_too_long"];
    }
    
    // 로컬 파트(골뱅이 앞 부분) 길이 확인
    const atIndex = email.indexOf('@');
    if (atIndex > 64) {
        return [false, "local_part_too_long"];
    }
    
    // 기본 패턴 검증
    if (!emailPattern.test(email)) {
        return [false, "invalid_pattern"];
    }
    
    // 도메인 부분 검증
    const domainPart = email.substring(atIndex + 1);
    
    // 도메인에 연속된 마침표 금지
    if (domainPart.includes('..')) {
        return [false, "consecutive_dots_in_domain"];
    }
    
    // 도메인 레이블 길이 확인 (각 레이블은 63자 이하)
    const domainLabels = domainPart.split('.');
    for (const label of domainLabels) {
        if (label.length > 63) {
            return [false, "domain_label_too_long"];
        }
    }
    
    // 최상위 도메인(TLD)이 최소 2자 이상인지 확인 (일반적인 경우)
    const tld = domainLabels[domainLabels.length - 1];
    if (tld.length < 2) {
        return [false, "tld_too_short"];
    }
    
    // 모든 검증 통과
    return [true, "valid_email_format"];
};