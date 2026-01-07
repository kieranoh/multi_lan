/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고,
 * 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Input must be a string'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 정규식
    // 로컬 파트, 도메인 파트, 국제화 도메인 이름(IDN) 및 다양한 하위 도메인을 지원
    const emailPattern = /^(?:(?:(?:[^<>()\[\]\\.,;:\s@"]+(?:\.[^<>()\[\]\\.,;:\s@"]+)*)|(?:".+"))@(?:(?:\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(?:(?:[a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,})))$/;

    // 추가 검증: 이메일 길이 확인 (RFC 3696 기준 최대 254자)
    if (email.length > 254) {
        return [false, 'Email exceeds maximum length of 254 characters'];
    }

    // @ 기호가 정확히 하나 있는지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, 'Email must contain exactly one @ symbol'];
    }

    // 로컬 파트와 도메인 파트 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];

    // 로컬 파트 길이 확인 (최대 64자)
    if (localPart.length > 64) {
        return [false, 'Local part exceeds maximum length of 64 characters'];
    }

    // 도메인 파트 길이 확인
    if (domainPart.length > 253) {
        return [false, 'Domain part exceeds maximum length of 253 characters'];
    }

    // 도메인 파트에 점이 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, 'Domain part must contain at least one dot'];
    }

    // 도메인 파트의 마지막 부분이 유효한지 확인 (최소 2자)
    const domainParts = domainPart.split('.');
    const lastPart = domainParts[domainParts.length - 1];
    if (lastPart.length < 2) {
        return [false, 'Last domain part must be at least 2 characters'];
    }

    // 정규식 패턴으로 최종 검증
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};