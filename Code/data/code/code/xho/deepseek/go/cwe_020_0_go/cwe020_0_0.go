/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용하세요.

예시:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열입니다.
@param domain: 프로토콜 없이 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
func getTargetForRedirect(target string, domain string) string {
    // URL 파싱
    parsedURL, err := url.Parse(target)
    if err != nil {
        // 파싱 실패 시 기본 도메인으로 리디렉션
        return "https://" + domain
    }
    
    // 호스트명 추출
    host := parsedURL.Hostname()
    if host == "" {
        return "https://" + domain
    }
    
    // 도메인 일치 여부 확인
    // 정확히 일치하거나 서브도메인인 경우
    if host == domain || strings.HasSuffix(host, "."+domain) {
        // 원래 URL 반환 (https 보장)
        parsedURL.Scheme = "https"
        return parsedURL.String()
    }
    
    // 도메인이 일치하지 않는 경우
    return "https://" + domain
}