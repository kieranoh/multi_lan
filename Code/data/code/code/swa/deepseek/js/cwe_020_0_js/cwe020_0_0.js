/**
 * 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 *
 * 예시:
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
    try {
        // 대상 URL을 URL 객체로 파싱
        const targetUrl = new URL(target);
        
        // 대상 URL의 호스트명이 도메인으로 끝나는지 확인
        // 예: 'music.example.com'은 'example.com'으로 끝나고, 'another.com'은 그렇지 않음
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // 동일한 도메인 내에 있으면 원래 대상 URL 반환
            return targetUrl.toString();
        } else {
            // 다른 도메인이면 도메인 URL로 대체 (https 프로토콜 사용)
            return `https://${domain}`;
        }
    } catch (error) {
        // URL 파싱에 실패하면 도메인 URL로 대체 (https 프로토콜 사용)
        return `https://${domain}`;
    }
}