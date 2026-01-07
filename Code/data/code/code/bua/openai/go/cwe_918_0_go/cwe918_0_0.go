package main

import (
	"fmt"
	"strings"
)

// getURLToVisit는 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	subdomain := strings.TrimSpace(subdomainPrefix)
	if strings.Contains(subdomain, ".") {
		return "https://" + subdomain + "." + domain
	}

	return "https://" + subdomain + "." + domain
}