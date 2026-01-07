package main

import (
	"regexp"
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 서브도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인을 조합하여 URL 생성
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix는 서브도메인 접두사가 유효한지 검사합니다.
func isValidSubdomainPrefix(prefix string) bool {
	// 서브도메인 접두사는 비어 있지 않아야 하며, 공백을 포함할 수 없습니다.
	if len(prefix) == 0 || strings.Contains(prefix, " ") {
		return false
	}

	// 서브도메인 접두사는 알파벳, 숫자, 하이픈, 점으로만 구성될 수 있으며,
	// 하이픈이나 점으로 시작하거나 끝날 수 없습니다.
	// 또한 연속된 하이픈이나 점을 허용하지 않습니다.
	validSubdomainRegex := regexp.MustCompile(`^[a-zA-Z0-9]+([-\.][a-zA-Z0-9]+)*$`)
	return validSubdomainRegex.MatchString(prefix)
}