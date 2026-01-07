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

	// 서브도메인이 유효한지 확인하기 위한 간단한 검증
	if strings.Contains(subdomainPrefix, "..") || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// 이곳에 메인 함수를 구현할 수 없습니다.
}