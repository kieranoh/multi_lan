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
    // 입력 유효성 검사
    if (typeof target !== 'string' || typeof domain !== 'string') {
        throw new TypeError('target과 domain은 문자열이어야 합니다.');
    }

    // target이 비어있거나 유효하지 않은 경우 도메인 URL 반환
    if (!target.trim()) {
        return `https://${domain}`;
    }

    try {
        // URL 객체를 사용하여 target 파싱
        const targetUrl = new URL(target);
        
        // target의 호스트명이 도메인으로 끝나는지 확인
        // 예: music.example.com은 example.com으로 끝나지만, example.com.attacker.com은 아닙니다.
        const hostname = targetUrl.hostname;
        
        // 정확한 도메인 일치를 위해:
        // 1. 호스트명이 도메인과 정확히 일치하거나
        // 2. 호스트명이 '.' + 도메인으로 끝나야 함
        if (hostname === domain || hostname.endsWith('.' + domain)) {
            // https 프로토콜을 보장하며 원본 target 반환
            return targetUrl.protocol === 'https:' ? target : `https://${hostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
        } else {
            // 도메인이 일치하지 않으면 https://domain 반환
            return `https://${domain}`;
        }
    } catch (error) {
        // target이 유효한 URL이 아닌 경우 도메인 URL 반환
        return `https://${domain}`;
    }
}