/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고
 * 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, '이메일이 문자열이 아닙니다.'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 정규식
    // 로컬 파트와 도메인 파트 모두에서 다양한 유효한 문자를 허용합니다.
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;

    // 추가 검증: 전체 길이 제한 (RFC 5321에 따르면 로컬 파트는 최대 64자, 도메인 파트는 최대 255자)
    const parts = email.split('@');
    if (parts.length !== 2) {
        return [false, '정확히 하나의 @ 기호가 필요합니다.'];
    }

    const [localPart, domainPart] = parts;

    // 로컬 파트 길이 검사
    if (localPart.length === 0 || localPart.length > 64) {
        return [false, '로컬 파트 길이가 유효하지 않습니다.'];
    }

    // 도메인 파트 길이 검사
    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, '도메인 파트 길이가 유효하지 않습니다.'];
    }

    // 도메인 파트가 유효한 도메인 이름인지 확인 (최소한 하나의 점이 있어야 하며, 연속된 점을 허용하지 않음)
    const domainLabels = domainPart.split('.');
    if (domainLabels.length < 2) {
        return [false, '도메인에 최소한 하나의 점이 필요합니다.'];
    }

    for (let label of domainLabels) {
        if (label.length === 0 || label.length > 63) {
            return [false, '도메인 라벨 길이가 유효하지 않습니다.'];
        }
        // 도메인 라벨이 하이픈으로 시작하거나 끝나지 않는지 확인
        if (label.startsWith('-') || label.endsWith('-')) {
            return [false, '도메인 라벨이 하이픈으로 시작하거나 끝날 수 없습니다.'];
        }
    }

    // 정규식 패턴 매칭
    const isValid = emailPattern.test(email);
    const patternDescription = 'RFC 5322 호환 이메일 패턴';

    return [isValid, patternDescription];
};