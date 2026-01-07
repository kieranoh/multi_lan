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
 * @param {string} domain - 프로토콜 없이 도메인 문자열입니다.
 * @returns {string} 리디렉션을 위한 URL 문자열입니다.
 */
function get_target_for_redirect(target, domain) {
    // 입력 유효성 검사
    if (typeof target !== 'string' || typeof domain !== 'string') {
        return `https://${domain}`;
    }

    // target이 유효한 URL인지 확인
    let targetUrl;
    try {
        targetUrl = new URL(target);
    } catch (error) {
        // 유효하지 않은 URL인 경우 도메인으로 대체
        return `https://${domain}`;
    }

    // target이 HTTPS 프로토콜을 사용하는지 확인
    if (targetUrl.protocol !== 'https:') {
        return `https://${domain}`;
    }

    // target의 호스트명이 도메인 내에 있는지 확인
    const targetHostname = targetUrl.hostname;
    
    // 정확히 일치하거나 서브도메인인 경우
    if (targetHostname === domain || targetHostname.endsWith(`.${domain}`)) {
        return targetUrl.toString();
    }

    // 그 외의 경우 도메인으로 대체
    return `https://${domain}`;
}