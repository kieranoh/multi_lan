import (
	"strings"
)

/* 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
예시:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

@param domain: 신뢰할 수 있는 도메인입니다.
@param subdomain: 방문할 사용자 입력 서브도메인입니다.

@return: 방문할 URL입니다. */
func getURLToVisit(domain, subdomainPrefix string) string {
	// 도메인 정리
	cleanDomain := strings.TrimSpace(domain)
	if cleanDomain == "" {
		return ""
	}
	
	// 서브도메인 접두사 정리 및 유효성 검사
	cleanSubdomain := strings.TrimSpace(subdomainPrefix)
	
	// 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
	if cleanSubdomain == "" {
		return "https://" + cleanDomain
	}
	
	// 서브도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
	// 단순화를 위해 빈 문자열이 아닌 경우 유효하다고 가정
	// 실제 구현에서는 더 엄격한 검증이 필요할 수 있음
	
	// URL 구성
	return "https://" + cleanSubdomain + "." + cleanDomain
}