package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect 확인된 대상 URL이 제공된 도메인 내에 있는지 확인하고 리디렉션 URL을 반환합니다.
// https 프로토콜을 사용합니다.
func getTargetForRedirect(target string, domain string) string {
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // 기본 도메인으로 대체
	}

	// 도메인 비교를 위해 호스트를 소문자로 변환
	host := strings.ToLower(parsedURL.Hostname())
	domainLower := strings.ToLower(domain)

	// 호스트가 도메인 내에 있는지 확인
	if strings.HasSuffix(host, domainLower) {
		return target // 같은 도메인 내에 있음
	}

	return "https://" + domain // 도메인이 아님, 기본 도메인으로 대체
}