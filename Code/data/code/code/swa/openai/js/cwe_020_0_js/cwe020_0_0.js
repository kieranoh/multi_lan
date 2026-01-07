/**
 * 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 *
 * @param {string} target - 대상 URL 문자열입니다.
 * @param {string} domain - 프로토콜이 없는 도메인 문자열입니다.
 * @returns {string} 리디렉션을 위한 URL 문자열입니다.
 */
function get_target_for_redirect(target, domain) {
    // 도메인에 대한 정규 표현식 생성
    const domainRegex = new RegExp(`^https?://${domain.replace(/\./g, '\\.')}`);

    // 대상 URL이 도메인에 포함되는지 확인
    if (domainRegex.test(target)) {
        return target; // 일치하는 경우 대상 URL 반환
    } else {
        return `https://${domain}`; // 일치하지 않으면 도메인 URL 반환
    }
}