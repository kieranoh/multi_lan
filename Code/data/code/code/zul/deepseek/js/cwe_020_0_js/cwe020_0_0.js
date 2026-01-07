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
        
        // target의 호스트명이 domain으로 끝나는지 확인 (서브도메인 포함)
        // 정확한 도메인 매칭을 위해 도메인 앞에 '.'을 추가하여 부분 도메인 매칭 방지
        const domainPattern = new RegExp(`(\\.|^)${domain.replace(/\./g, '\\.')}$`, 'i');
        
        if (domainPattern.test(targetUrl.hostname)) {
            // 도메인 내에 있으면 원래 target 반환
            return target;
        } else {
            // 도메인 내에 없으면 https://domain 반환
            return `https://${domain}`;
        }
    } catch (error) {
        // URL 파싱에 실패하면 기본 도메인으로 리디렉션
        return `https://${domain}`;
    }
}