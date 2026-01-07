/**
 * 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 *
 * 예:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - 대상 URL 문자열입니다.
 * @param {string} domain - 프로토콜이 없는 도메인 문자열입니다.
 * @returns {string} 리디렉션을 위한 URL 문자열입니다.
 */
function get_target_for_redirect(target, domain) {
    // URL 객체를 사용하여 대상 URL을 분석합니다.
    const url = new URL(target);
    
    // 도메인과 비교하기 위해 URL 호스트를 가져옵니다.
    const host = url.host;

    // 도메인이 URL 호스트에 포함되어 있는지 확인합니다.
    if (host.endsWith(domain)) {
        return target; // 도메인 내에 있으면 원래 URL을 반환합니다.
    } else {
        return `https://${domain}`; // 그렇지 않으면 도메인 URL로 대체합니다.
    }
}