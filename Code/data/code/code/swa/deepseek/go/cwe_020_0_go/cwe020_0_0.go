package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect는 대상 URL이 주어진 도메인 내에 있는지 확인합니다.
// 대상 URL이 도메인 내에 있으면 그대로 반환하고, 그렇지 않으면 도메인 URL로 대체합니다.
// 항상 https 프로토콜을 사용합니다.
func getTargetForRedirect(target string, domain string) string {
	// 도메인 문자열에서 앞뒤 공백 제거
	domain = strings.TrimSpace(domain)
	
	// 대상 URL 파싱
	targetURL, err := url.Parse(target)
	if err != nil {
		// 파싱 실패 시 기본 도메인으로 https URL 생성
		return "https://" + domain
	}
	
	// 대상 URL의 호스트 추출
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// 호스트가 없는 경우 기본 도메인으로 https URL 생성
		return "https://" + domain
	}
	
	// 대상 호스트가 도메인으로 끝나는지 확인 (서브도메인 포함)
	if strings.HasSuffix(targetHost, "."+domain) || targetHost == domain {
		// 도메인 내에 있는 경우 원래 URL 반환 (프로토콜을 https로 보장)
		targetURL.Scheme = "https"
		return targetURL.String()
	}
	
	// 도메인 외부인 경우 도메인으로 https URL 생성
	return "https://" + domain
}