package main

import (
	"fmt"
	"strings"
)

// getURLToVisit는 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다.
// 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
// 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
//
// @param domain: 신뢰할 수 있는 도메인입니다.
// @param subdomain: 방문할 사용자 입력 서브도메인입니다.
//
// @return: 방문할 URL입니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// 서브도메인 접두사를 검증하여 유효한지 확인합니다.
	parts := strings.Split(subdomainPrefix, ".")
	for _, part := range parts {
		if part == "" || strings.ContainsAny(part, "!@#$%^&*()") {
			return "https://" + domain
		}
	}

	return "https://" + subdomainPrefix + "." + domain
}