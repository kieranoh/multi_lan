/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고,
 *                                 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, '이메일은 문자열이어야 합니다.'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 정규식
    // 국제화된 도메인 이름(IDN)과 다양한 하위 도메인을 지원
    const emailPattern = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;

    // 추가적인 엄격한 검증을 위한 패턴
    const strictEmailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;

    // 더 포괄적인 검증을 위한 패턴 (더 많은 특수문자 허용)
    const comprehensivePattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;

    // 최종적으로 사용할 패턴 선택 (comprehensivePattern 사용)
    const finalPattern = comprehensivePattern;

    // 이메일 길이 검증 (RFC 5321 기준: 로컬 파트 64자, 도메인 파트 255자)
    const atIndex = email.indexOf('@');
    if (atIndex === -1) {
        return [false, '이메일 형식에 @가 포함되어야 합니다.'];
    }

    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);

    if (localPart.length === 0 || localPart.length > 64) {
        return [false, '로컬 파트(사용자 이름)는 1자 이상 64자 이하여야 합니다.'];
    }

    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, '도메인 파트는 1자 이상 255자 이하여야 합니다.'];
    }

    // 전체 이메일 길이 검증 (RFC 5321 기준: 최대 254자)
    if (email.length > 254) {
        return [false, '이메일 주소는 254자를 초과할 수 없습니다.'];
    }

    // 도메인 파트에 연속된 점(.)이 있는지 확인
    if (domainPart.includes('..')) {
        return [false, '도메인 파트에 연속된 점(.)이 포함될 수 없습니다.'];
    }

    // 로컬 파트에 연속된 점(.)이 있는지 확인
    if (localPart.includes('..')) {
        return [false, '로컬 파트에 연속된 점(.)이 포함될 수 없습니다.'];
    }

    // 도메인 파트의 시작이나 끝에 점(.)이 있는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, '도메인 파트는 점(.)으로 시작하거나 끝날 수 없습니다.'];
    }

    // 최상위 도메인(TLD)이 최소 2자 이상인지 확인
    const domainParts = domainPart.split('.');
    if (domainParts.length < 2) {
        return [false, '도메인 파트는 최소 하나의 점(.)을 포함해야 합니다.'];
    }

    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, '최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.'];
    }

    // 정규식 패턴으로 최종 검증
    const isValid = finalPattern.test(email);

    return [isValid, isValid ? 'RFC 5322 호환 이메일 패턴' : '이메일 형식이 올바르지 않습니다.'];
};