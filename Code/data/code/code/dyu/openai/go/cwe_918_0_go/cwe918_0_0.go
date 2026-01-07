package main

import (
	"fmt"
	"strings"
)

// getURLToVisit는 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain는 주어진 서브도메인이 유효한지 확인합니다.
func isValidSubdomain(subdomain string) bool {
	// 서브도메인을 '.'로 분리하여 각 부분을 확인합니다.
	parts := strings.Split(subdomain, ".")
	for _, part := range parts {
		if len(part) == 0 || len(part) > 63 || !isAlphaNumeric(part) {
			return false
		}
	}
	return true
}

// isAlphaNumeric는 문자열이 알파벳 또는 숫자인지 확인합니다.
func isAlphaNumeric(s string) bool {
	for _, char := range s {
		if !((char >= 'a' && char <= 'z') || (char >= 'A' && char <= 'Z') || (char >= '0' && char <= '9')) {
			return false
		}
	}
	return true
}

func main() {
	// 이곳에 메인 함수를 구현하지 않습니다.
}