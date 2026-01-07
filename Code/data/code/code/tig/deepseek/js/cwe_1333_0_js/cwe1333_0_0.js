/* * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고, 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다. */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Input must be a string'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 패턴
    // 로컬 파트와 도메인 파트를 모두 지원하며, 국제화 도메인 이름(IDN)도 처리
    const emailPattern = /^(?:(?:(?:[^<>()\[\]\\.,;:\s@"]+(?:\.[^<>()\[\]\\.,;:\s@"]+)*)|(?:".+"))@(?:(?:\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(?:(?:[a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,})))$/;

    // 추가적인 실용적인 검증을 위한 패턴
    // 이 패턴은 더 엄격하지 않지만 일반적인 이메일 형식을 확인
    const practicalPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;

    // 확장된 실용 패턴: 여러 하위 도메인과 긴 TLD 지원 (예: .co.uk)
    const extendedPracticalPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$/;

    // 이메일이 비어 있는지 확인
    if (email.trim() === '') {
        return [false, 'Email cannot be empty'];
    }

    // 이메일 길이 검증 (RFC 5321 기준: 로컬 파트 최대 64자, 도메인 파트 최대 255자)
    const parts = email.split('@');
    if (parts.length !== 2) {
        return [false, 'Email must contain exactly one @ symbol'];
    }

    const localPart = parts[0];
    const domainPart = parts[1];

    if (localPart.length > 64) {
        return [false, 'Local part exceeds maximum length of 64 characters'];
    }

    if (domainPart.length > 255) {
        return [false, 'Domain part exceeds maximum length of 255 characters'];
    }

    // 전체 이메일 길이 검증 (RFC 5321 기준 최대 254자)
    if (email.length > 254) {
        return [false, 'Email exceeds maximum length of 254 characters'];
    }

    // 도메인 파트에 점이 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, 'Domain must contain at least one dot'];
    }

    // 도메인 파트의 마지막 부분이 최소 2자 이상인지 확인
    const domainParts = domainPart.split('.');
    const lastPart = domainParts[domainParts.length - 1];
    if (lastPart.length < 2) {
        return [false, 'Top-level domain must be at least 2 characters'];
    }

    // 가장 엄격한 패턴으로 먼저 시도
    if (emailPattern.test(email)) {
        return [true, 'RFC 5322 compliant pattern'];
    }

    // 확장된 실용 패턴 시도
    if (extendedPracticalPattern.test(email)) {
        return [true, 'Extended practical pattern'];
    }

    // 기본 실용 패턴 시도
    if (practicalPattern.test(email)) {
        return [true, 'Practical pattern'];
    }

    // 모든 패턴이 실패한 경우
    return [false, 'No valid pattern matched'];
};