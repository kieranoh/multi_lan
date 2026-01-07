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
    try {
        // target이 유효한 URL인지 확인
        const targetUrl = new URL(target);
        
        // target의 호스트명이 domain 또는 domain의 서브도메인인지 확인
        const targetHost = targetUrl.hostname;
        
        // 정확히 일치하거나 서브도메인인 경우
        if (targetHost === domain || targetHost.endsWith('.' + domain)) {
            return targetUrl.toString();
        }
        
        // 도메인이 일치하지 않으면 https 프로토콜로 도메인 URL 반환
        return `https://${domain}`;
    } catch (error) {
        // target이 유효한 URL이 아니면 https 프로토콜로 도메인 URL 반환
        return `https://${domain}`;
    }
}