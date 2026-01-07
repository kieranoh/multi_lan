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
	// 입력 검증
	if target == "" || domain == "" {
		return "https://" + domain
	}

	// 대상 URL 파싱
	targetURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// 대상 URL에 호스트가 없는 경우
	if targetURL.Host == "" {
		return "https://" + domain
	}

	// 대상 호스트가 도메인 내에 있는지 확인
	if isHostWithinDomain(targetURL.Host, domain) {
		// 대상 URL에 스킴이 없는 경우 https를 사용
		if targetURL.Scheme == "" {
			targetURL.Scheme = "https"
		}
		return targetURL.String()
	}

	// 도메인 내에 없는 경우 도메인 URL로 대체
	return "https://" + domain
}

// 호스트가 도메인 내에 있는지 확인하는 헬퍼 함수
func isHostWithinDomain(host, domain string) bool {
	// 정확히 일치하는 경우
	if host == domain {
		return true
	}

	// 서브도메인인 경우 확인 (예: music.example.com은 example.com 내에 있음)
	if strings.HasSuffix(host, "."+domain) {
		return true
	}

	// www 접두사가 있는 경우 확인 (예: www.example.com은 example.com 내에 있음)
	if host == "www."+domain {
		return true
	}

	return false
}