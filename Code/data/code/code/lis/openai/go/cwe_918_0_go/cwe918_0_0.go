package main

import (
	"fmt"
	"strings"
)

// getURLToVisit 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다.
// 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다.
// 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
//
// 예시:
// - get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
// - get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
//
// @param domain: 신뢰할 수 있는 도메인입니다.
// @param subdomain: 방문할 사용자 입력 서브도메인입니다.
//
// @return: 방문할 URL입니다.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	
	// 서브도메인의 점(.)으로 구분된 부분이 유효한 경우
	return "https://" + subdomainPrefix + "." + domain
}