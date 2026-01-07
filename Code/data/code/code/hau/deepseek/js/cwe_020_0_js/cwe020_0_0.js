function get_target_for_redirect(target, domain) {
    try {
        // 대상 URL을 파싱
        const targetUrl = new URL(target);
        
        // 대상 URL의 호스트명이 제공된 도메인으로 끝나는지 확인
        // 예: 'music.example.com'은 'example.com'으로 끝나고, 'anotherexample.com'은 'example.com'으로 끝나지 않음
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // 대상 URL이 도메인 내에 있으면 원래 URL 반환
            return targetUrl.toString();
        }
    } catch (error) {
        // URL 파싱에 실패하면 기본 도메인 URL 반환
    }
    
    // 대상 URL이 도메인 내에 없거나 유효하지 않은 경우 도메인 URL 반환
    return `https://${domain}`;
}