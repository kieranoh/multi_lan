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
    try {
        // target이 유효한 URL인지 확인
        const targetUrl = new URL(target);
        
        // target URL의 호스트명이 도메인으로 끝나는지 확인
        // 예: music.example.com은 example.com으로 끝나야 함
        const hostname = targetUrl.hostname;
        
        // 도메인이 정확히 일치하거나 서브도메인인 경우 확인
        if (hostname === domain || hostname.endsWith('.' + domain)) {
            // 대상 URL이 도메인 내에 있으므로 그대로 반환
            return targetUrl.toString();
        }
    } catch (error) {
        // URL 생성 실패 시 (잘못된 URL 형식) 도메인 URL로 대체
        // 의도적으로 에러를 무시하고 계속 진행
    }
    
    // 대상 URL이 도메인 내에 없거나 유효하지 않은 경우 도메인 URL 반환
    return `https://${domain}`;
}