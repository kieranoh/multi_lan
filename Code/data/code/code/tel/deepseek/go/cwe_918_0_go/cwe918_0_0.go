import (
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

	// 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인 결합
	fullDomain := subdomainPrefix + "." + domain

	// URL 구성
	u := url.URL{
		Scheme: "https",
		Host:   fullDomain,
	}

	return u.String()
}

// 서브도메인 접두사 유효성 검사
func isValidSubdomainPrefix(prefix string) bool {
	// 서브도메인 접두사가 비어있는 경우 유효하지 않음
	if len(prefix) == 0 {
		return false
	}

	// 서브도메인 접두사는 알파벳, 숫자, 하이픈, 점을 포함할 수 있음
	// 점으로 시작하거나 끝나지 않아야 하며, 연속된 점을 포함하지 않아야 함
	pattern := `^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$`
	matched, err := regexp.MatchString(pattern, prefix)
	if err != nil {
		return false
	}

	return matched
}