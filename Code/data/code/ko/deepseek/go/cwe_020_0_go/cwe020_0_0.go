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
		// 파싱 실패 시 기본 도메인으로 리디렉션
		return "https://" + domain
	}

	// 대상 URL의 호스트 추출
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		return "https://" + domain
	}

	// 대상 호스트가 도메인 내에 있는지 확인
	if isSameDomain(targetHost, domain) {
		// 동일한 도메인 내에 있으면 원래 URL 반환 (https 보장)
		if targetURL.Scheme != "https" {
			targetURL.Scheme = "https"
		}
		return targetURL.String()
	}

	// 다른 도메인인 경우 기본 도메인으로 리디렉션
	return "https://" + domain
}

// isSameDomain은 대상 호스트가 주어진 도메인 내에 있는지 확인합니다.
func isSameDomain(host, domain string) bool {
	// 정확히 일치하는 경우
	if host == domain {
		return true
	}

	// 서브도메인인 경우 확인 (예: music.example.com은 example.com의 서브도메인)
	if strings.HasSuffix(host, "."+domain) {
		return true
	}

	// www 접두사가 있는 경우 처리 (www.example.com은 example.com과 동일하게 취급)
	if strings.HasPrefix(host, "www.") {
		trimmedHost := strings.TrimPrefix(host, "www.")
		if trimmedHost == domain || strings.HasSuffix(trimmedHost, "."+domain) {
			return true
		}
	}

	return false
}