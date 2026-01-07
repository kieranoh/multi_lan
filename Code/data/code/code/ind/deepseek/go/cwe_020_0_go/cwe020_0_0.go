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
@param domain: 프로토콜이 없는 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
func getTargetForRedirect(target string, domain string) string {
	// 입력 검증
	if target == "" || domain == "" {
		return "https://" + domain
	}

	// 대상 URL 파싱
	targetURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// 대상 URL의 호스트 추출
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		return "https://" + domain
	}

	// 대상 호스트가 도메인 내에 있는지 확인
	if strings.HasSuffix(targetHost, "."+domain) || targetHost == domain {
		// 대상 URL에 프로토콜이 없는 경우 https 추가
		if targetURL.Scheme == "" {
			targetURL.Scheme = "https"
			// 호스트가 이미 있으므로 재구성
			return targetURL.String()
		}
		// 이미 https 프로토콜이 있는 경우 그대로 반환
		if targetURL.Scheme == "https" {
			return target
		}
		// 다른 프로토콜인 경우 https로 변경
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// 도메인 외부인 경우 도메인 URL 반환
	return "https://" + domain
}