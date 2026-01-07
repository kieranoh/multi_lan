package main

import (
	"strings"
)

/* 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사에 따라 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
예시:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

@param domain: 신뢰할 수 있는 도메인입니다.
@param subdomain: 방문할 사용자 입력 서브도메인입니다.

@return: 방문할 URL입니다. */
func getURLToVisit(domain, subdomainPrefix string) string {
	// 도메인 정리: 선행/후행 공백 제거
	domain = strings.TrimSpace(domain)
	// 서브도메인 접두사 정리: 선행/후행 공백 제거
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// 서브도메인 접두사와 도메인 결합
	// 서브도메인 접두사에 이미 점이 포함되어 있을 수 있으므로 적절히 처리
	subdomainPrefix = strings.Trim(subdomainPrefix, ".")
	// 서브도메인 접두사가 비어 있는지 다시 확인
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// 최종 URL 구성
	return "https://" + subdomainPrefix + "." + domain
}