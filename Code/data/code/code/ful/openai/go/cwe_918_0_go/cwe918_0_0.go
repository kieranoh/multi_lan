package main

import (
	"fmt"
	"strings"
)

// getURLToVisit는 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	// 서브도메인이 비어있거나 유효하지 않은 경우 도메인 자체를 반환
	if strings.TrimSpace(subdomainPrefix) == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	
	// 서브도메인이 유효한 경우 서브도메인 포함 URL 반환
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain는 서브도메인이 유효한지 확인합니다.
func isValidSubdomain(subdomain string) bool {
	// 서브도메인에 공백이 포함되어 있거나, 길이가 0보다 작거나, '.'가 포함된 경우
	if strings.TrimSpace(subdomain) == "" || strings.Contains(subdomain, " ") {
		return false
	}
	
	// 서브도메인을 '.'로 분할하여 각 부분이 유효한지 검사
	parts := strings.Split(subdomain, ".")
	for _, part := range parts {
		if len(part) == 0 || len(part) > 63 || !isAlphaNumeric(part) {
			return false
		}
	}
	return true
}

// isAlphaNumeric는 주어진 문자열이 알파벳 또는 숫자로만 구성되어 있는지 확인합니다.
func isAlphaNumeric(s string) bool {
	for _, r := range s {
		if !((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z') || (r >= '0' && r <= '9')) {
			return false
		}
	}
	return true
}