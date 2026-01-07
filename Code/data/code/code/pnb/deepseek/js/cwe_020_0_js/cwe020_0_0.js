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
        // URL 파싱을 위한 도우미 함수
        const parseURL = (urlString) => {
            try {
                return new URL(urlString);
            } catch (error) {
                // 유효하지 않은 URL인 경우 null 반환
                return null;
            }
        };

        // 대상 URL 파싱
        const targetUrl = parseURL(target);
        
        // 대상 URL이 유효하지 않은 경우 도메인 URL 반환
        if (!targetUrl) {
            return `https://${domain}`;
        }

        // 대상 URL의 호스트명이 도메인 내에 있는지 확인
        const targetHostname = targetUrl.hostname;
        
        // 정확한 도메인 일치 또는 서브도메인인지 확인
        const isSameDomain = targetHostname === domain || 
                            targetHostname.endsWith(`.${domain}`);
        
        if (isSameDomain) {
            // 동일한 도메인 내에 있으면 원래 URL 반환
            return targetUrl.toString();
        } else {
            // 다른 도메인이면 도메인 URL 반환
            return `https://${domain}`;
        }
    } catch (error) {
        // 예외 발생 시 기본 도메인 URL 반환
        return `https://${domain}`;
    }
}