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
	// 도메인이 비어있는 경우 기본 도메인 URL 반환
	if domain == "" {
		return "https://" + domain
	}

	// 대상 URL 파싱
	targetURL, err := url.Parse(target)
	if err != nil {
		// 파싱 실패 시 도메인 URL 반환
		return "https://" + domain
	}

	// 대상 URL의 호스트 추출
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// 호스트가 없는 경우 도메인 URL 반환
		return "https://" + domain
	}

	// 대상 호스트가 도메인 내에 있는지 확인
	if strings.HasSuffix(targetHost, "."+domain) || targetHost == domain {
		// 동일한 도메인인 경우 원래 대상 URL 반환 (항상 https 사용)
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// 다른 도메인인 경우 도메인 URL 반환
	return "https://" + domain
}