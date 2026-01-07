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
        return `https://${domain}`;
    }

    try {
        // 대상 URL 파싱
        const targetUrl = new URL(target);
        
        // 대상 URL의 호스트명이 도메인으로 끝나는지 확인
        // 예: 'music.example.com'은 'example.com'으로 끝나야 함
        // 단순한 문자열 끝 비교가 아닌 도메인 일치 검사
        const targetHost = targetUrl.hostname;
        
        // 도메인 일치 검사: 정확히 동일하거나 서브도메인인 경우
        if (targetHost === domain || targetHost.endsWith(`.${domain}`)) {
            // 대상 URL이 이미 https인지 확인
            if (targetUrl.protocol === 'https:') {
                return targetUrl.toString();
            } else {
                // https로 강제 변환
                return `https://${targetHost}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
            }
        } else {
            // 도메인이 일치하지 않으면 기본 도메인으로 리디렉션
            return `https://${domain}`;
        }
    } catch (error) {
        // URL 파싱 실패 시 (잘못된 URL 형식) 기본 도메인으로 리디렉션
        return `https://${domain}`;
    }
}