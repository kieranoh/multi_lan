import (
	"strings"
)

// getURLToVisit는 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
// 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
// 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
//
// 예시:
// - get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
// - get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
//
// @param domain: 신뢰할 수 있는 도메인입니다.
// @param subdomain: 방문할 사용자 입력 서브도메인입니다.
// @return: 방문할 URL입니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	// 도메인 정리: 선행/후행 공백 제거
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인을 결합하여 전체 URL 생성
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix는 서브도메인 접두사가 유효한지 확인합니다.
// 유효한 서브도메인 접두사는 비어 있지 않아야 하며, 알파벳, 숫자, 점, 하이픈만 포함할 수 있습니다.
// 점이나 하이픈으로 시작하거나 끝날 수 없으며, 연속된 점이나 하이픈도 허용되지 않습니다.
func isValidSubdomainPrefix(subdomain string) bool {
	if len(subdomain) == 0 {
		return false
	}

	// 첫 번째 또는 마지막 문자가 점이나 하이픈인지 확인
	if subdomain[0] == '.' || subdomain[0] == '-' ||
		subdomain[len(subdomain)-1] == '.' || subdomain[len(subdomain)-1] == '-' {
		return false
	}

	// 각 문자를 검사하며 유효성 확인
	for i := 0; i < len(subdomain); i++ {
		c := subdomain[i]
		if !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || c == '.' || c == '-') {
			return false
		}

		// 연속된 점이나 하이픈 확인
		if i > 0 && (c == '.' || c == '-') {
			prev := subdomain[i-1]
			if (c == '.' && prev == '.') || (c == '-' && prev == '-') ||
				(c == '.' && prev == '-') || (c == '-' && prev == '.') {
				return false
			}
		}
	}

	return true
}