import (
	"fmt"
	"net/url"
	"regexp"
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 도메인과 서브도메인 접두사 정리
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// 도메인이 비어있는 경우 빈 문자열 반환
	if domain == "" {
		return ""
	}

	// 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인만 사용
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return fmt.Sprintf("https://%s", domain)
	}

	// 서브도메인 접두사와 도메인 결합
	fullDomain := fmt.Sprintf("%s.%s", subdomainPrefix, domain)
	
	// URL 생성
	return fmt.Sprintf("https://%s", fullDomain)
}

// isValidSubdomainPrefix는 서브도메인 접두사가 유효한지 확인합니다.
func isValidSubdomainPrefix(subdomain string) bool {
	// 서브도메인은 비어있지 않아야 하며, 점으로 시작하거나 끝나지 않아야 합니다.
	if subdomain == "" || strings.HasPrefix(subdomain, ".") || strings.HasSuffix(subdomain, ".") {
		return false
	}

	// 서브도메인 부분을 점으로 분리
	parts := strings.Split(subdomain, ".")
	for _, part := range parts {
		// 각 부분이 비어있지 않고 유효한 서브도메인 이름인지 확인
		if part == "" || !isValidSubdomainPart(part) {
			return false
		}
	}

	return true
}

// isValidSubdomainPart는 서브도메인의 각 부분이 유효한지 확인합니다.
func isValidSubdomainPart(part string) bool {
	// 서브도메인 부분은 문자로 시작하고 끝나야 하며, 알파벳, 숫자, 하이픈만 포함할 수 있습니다.
	// 하이픈으로 시작하거나 끝날 수 없습니다.
	pattern := `^[a-zA-Z0-9]([a-zA-Z0-9-]*[a-zA-Z0-9])?$`
	matched, err := regexp.MatchString(pattern, part)
	if err != nil {
		return false
	}
	return matched
}