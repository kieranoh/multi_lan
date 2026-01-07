package main

import (
	"regexp"
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
	// 도메인이 비어있는 경우 빈 문자열 반환
	if domain == "" {
		return ""
	}

	// 서브도메인 접두사가 비어있거나 유효하지 않은 경우 도메인만 반환
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인을 결합하여 URL 생성
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain은 서브도메인이 유효한지 검사합니다.
// 유효한 서브도메인은 다음 조건을 만족해야 합니다:
// - 빈 문자열이 아니어야 함
// - 알파벳, 숫자, 하이픈(-)만 포함할 수 있음
// - 하이픈으로 시작하거나 끝날 수 없음
// - 점(.)으로 구분된 각 부분이 위 조건을 만족해야 함
func isValidSubdomain(subdomain string) bool {
	if subdomain == "" {
		return false
	}

	// 점(.)으로 분리하여 각 부분 검사
	parts := strings.Split(subdomain, ".")
	for _, part := range parts {
		if part == "" {
			return false
		}

		// 각 부분이 알파벳, 숫자, 하이픈으로만 구성되었는지 확인
		matched, _ := regexp.MatchString(`^[a-zA-Z0-9][a-zA-Z0-9-]*[a-zA-Z0-9]$`, part)
		if !matched {
			return false
		}
	}

	return true
}