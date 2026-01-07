import (
	"net/url"
	"regexp"
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 도메인 정규화: 선행/후행 공백 제거
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// 도메인이 비어있는 경우 빈 문자열 반환
	if domain == "" {
		return ""
	}

	// 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인만 사용
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인 결합
	fullDomain := subdomainPrefix + "." + domain

	// URL 생성 및 반환
	return "https://" + fullDomain
}

// isValidSubdomainPrefix는 서브도메인 접두사가 유효한지 확인합니다.
func isValidSubdomainPrefix(subdomainPrefix string) bool {
	// 서브도메인 접두사가 비어있는 경우 유효하지 않음
	if subdomainPrefix == "" {
		return false
	}

	// 서브도메인 접두사가 점으로 시작하거나 끝나는 경우 유효하지 않음
	if strings.HasPrefix(subdomainPrefix, ".") || strings.HasSuffix(subdomainPrefix, ".") {
		return false
	}

	// 서브도메인 접두사에 연속된 점이 있는 경우 유효하지 않음
	if strings.Contains(subdomainPrefix, "..") {
		return false
	}

	// 서브도메인 접두사가 URL 인코딩이 필요한 문자를 포함하는지 확인
	// 안전한 문자만 허용: 알파벳, 숫자, 하이픈, 점
	validPattern := regexp.MustCompile(`^[a-zA-Z0-9.-]+$`)
	if !validPattern.MatchString(subdomainPrefix) {
		return false
	}

	// 각 라벨(점으로 구분된 부분)이 유효한지 확인
	labels := strings.Split(subdomainPrefix, ".")
	for _, label := range labels {
		// 라벨이 비어있는 경우 유효하지 않음
		if label == "" {
			return false
		}
		// 라벨이 하이픈으로 시작하거나 끝나는 경우 유효하지 않음
		if strings.HasPrefix(label, "-") || strings.HasSuffix(label, "-") {
			return false
		}
		// 라벨이 오직 숫자로만 구성된 경우 유효하지 않음 (RFC 1035)
		if isNumeric(label) {
			return false
		}
	}

	// 전체 서브도메인 접두사 길이 확인 (도메인 포함하지 않음)
	if len(subdomainPrefix) > 253 {
		return false
	}

	// 각 라벨 길이 확인 (RFC 1035)
	for _, label := range labels {
		if len(label) > 63 {
			return false
		}
	}

	return true
}

// isNumeric은 문자열이 오직 숫자로만 구성되어 있는지 확인합니다.
func isNumeric(s string) bool {
	for _, c := range s {
		if c < '0' || c > '9' {
			return false
		}
	}
	return true
}