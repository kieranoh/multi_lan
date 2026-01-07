package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect 확인합니다
// 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
// 그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
// https 프로토콜을 사용하세요.
func getTargetForRedirect(target string, domain string) string {
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	if strings.HasSuffix(parsedURL.Hostname(), domain) {
		return target
	}
	
	return "https://" + domain
}