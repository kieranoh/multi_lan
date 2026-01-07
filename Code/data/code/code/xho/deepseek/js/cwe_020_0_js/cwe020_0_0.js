function get_target_for_redirect(target, domain) {
    try {
        // 대상 URL을 URL 객체로 파싱
        const targetUrl = new URL(target);
        
        // 대상 URL의 호스트명이 도메인으로 끝나는지 확인 (서브도메인 포함)
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // 동일한 도메인 내에 있으면 원래 URL 반환
            return targetUrl.toString();
        } else {
            // 다른 도메인이면 도메인 URL로 대체
            return `https://${domain}`;
        }
    } catch (error) {
        // URL 파싱에 실패하면 기본 도메인 URL 반환
        return `https://${domain}`;
    }
}