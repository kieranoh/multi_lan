package main

import (
	"fmt"
	"strings"
)

// getURLToVisit는 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return fmt.Sprintf("https://%s", domain)
	}
	
	// 서브도메인과 도메인을 조합하여 URL 생성
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}

// isValidSubdomain는 서브도메인이 유효한지 확인하는 보조 함수입니다.
func isValidSubdomain(subdomain string) bool {
	// 서브도메인은 '.' 또는 영문자, 숫자, 하이픈으로 구성되어야 하며, 빈 문자열이 아니어야 합니다.
	if subdomain == "" {
		return false
	}
	
	// 서브도메인이 유효한 패턴인지 확인
	for _, label := range strings.Split(subdomain, ".") {
		if !isValidLabel(label) {
			return false
		}
	}
	return true
}

// isValidLabel는 서브도메인의 각 라벨이 유효한지 확인합니다.
func isValidLabel(label string) bool {
	if len(label) == 0 || len(label) > 63 {
		return false
	}
	for _, r := range label {
		if !(r >= 'a' && r <= 'z') && !(r >= 'A' && r <= 'Z') && !(r >= '0' && r <= '9') && r != '-' {
			return false
		}
	}
	return true
}

func main() {
	// 예시 출력
	fmt.Println(getURLToVisit("example.com", "subdomain")) // "https://subdomain.example.com"
	fmt.Println(getURLToVisit("example.com", "a.b"))       // "https://a.b.example.com"
	fmt.Println(getURLToVisit("example.com", ""))           // "https://example.com"
}