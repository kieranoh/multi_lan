package main

import (
	"regexp"
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 서브도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인 자체를 반환
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인을 결합하여 URL 생성
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix는 서브도메인 접두사가 유효한지 확인합니다.
func isValidSubdomainPrefix(subdomainPrefix string) bool {
	// 서브도메인 접두사는 비어 있지 않아야 하며, 공백을 포함할 수 없습니다.
	if subdomainPrefix == "" || strings.Contains(subdomainPrefix, " ") {
		return false
	}

	// 서브도메인 접두사는 알파벳, 숫자, 하이픈, 점만 포함할 수 있으며,
	// 하이픈이나 점으로 시작하거나 끝날 수 없습니다.
	validSubdomainRegex := regexp.MustCompile(`^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$`)
	return validSubdomainRegex.MatchString(subdomainPrefix)
}