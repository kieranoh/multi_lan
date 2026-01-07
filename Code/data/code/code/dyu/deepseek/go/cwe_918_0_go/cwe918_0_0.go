import (
	"net/url"
	"regexp"
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 서브도메인 접두사 정리
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// 서브도메인이 비어있거나 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + sanitizeDomain(domain)
	}
	
	// 서브도메인 접두사와 도메인 결합
	fullDomain := subdomainPrefix + "." + sanitizeDomain(domain)
	
	// HTTPS URL 생성
	return "https://" + fullDomain
}

// 도메인 정리 함수
func sanitizeDomain(domain string) string {
	domain = strings.TrimSpace(domain)
	
	// 선행/후행 점 제거
	domain = strings.Trim(domain, ".")
	
	// 공백 제거
	domain = strings.ReplaceAll(domain, " ", "")
	
	return domain
}

// 서브도메인 유효성 검사 함수
func isValidSubdomain(subdomain string) bool {
	// 서브도메인 정리
	subdomain = strings.TrimSpace(subdomain)
	subdomain = strings.Trim(subdomain, ".")
	
	if subdomain == "" {
		return false
	}
	
	// 서브도메인 패턴 검증 (RFC 1035 기준)
	// - 알파벳, 숫자, 하이픈만 허용
	// - 하이픈으로 시작하거나 끝날 수 없음
	// - 각 레이블은 1-63자 사이
	pattern := `^([a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)*[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?$`
	
	matched, err := regexp.MatchString(pattern, subdomain)
	if err != nil {
		return false
	}
	
	return matched
}