package main

import (
	"net/url"
	"strings"
)

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용하세요.

예시:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열입니다.
@param domain: 프로토콜 없이 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
func getTargetForRedirect(target string, domain string) string {
	// 먼저 대상 URL을 파싱합니다.
	targetURL, err := url.Parse(target)
	if err != nil {
		// 파싱에 실패하면 기본 도메인으로 https URL을 반환합니다.
		return "https://" + domain
	}

	// 대상 URL의 호스트가 도메인 내에 있는지 확인합니다.
	// 도메인 내에 있다는 것은 대상 호스트가 도메인과 정확히 일치하거나 도메인으로 끝나는 서브도메인인 경우입니다.
	if targetURL.Host == domain || strings.HasSuffix(targetURL.Host, "."+domain) {
		// 대상 URL이 이미 https 프로토콜을 사용하고 있는지 확인합니다.
		if targetURL.Scheme != "https" {
			targetURL.Scheme = "https"
			// Scheme을 변경한 후 URL을 재구성합니다.
			return targetURL.String()
		}
		return target
	}

	// 대상 URL이 도메인 내에 없으면 도메인으로 대체합니다.
	// https 프로토콜을 사용하여 새로운 URL을 구성합니다.
	return "https://" + domain
}