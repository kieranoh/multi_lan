package main

import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// 서브도메인 접두사 정리: 앞뒤 공백 제거
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// 서브도메인이 비어 있거나 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" || subdomainPrefix == "." {
		return "https://" + domain
	}
	
	// 서브도메인 접두사가 점으로 시작하거나 끝나지 않도록 정리
	subdomainPrefix = strings.Trim(subdomainPrefix, ".")
	
	// 서브도메인이 유효하지 않은 경우 도메인 자체 반환
	if subdomainPrefix == "" {
		return "https://" + domain
	}
	
	// 최종 URL 구성
	return "https://" + subdomainPrefix + "." + domain
}