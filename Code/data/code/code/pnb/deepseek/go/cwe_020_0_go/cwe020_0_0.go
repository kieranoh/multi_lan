package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect는 대상 URL이 주어진 도메인 내에 있는지 확인합니다.
// 대상 URL이 도메인 내에 있으면 해당 URL을 반환하고,
// 그렇지 않으면 도메인 URL로 대체합니다.
// 항상 https 프로토콜을 사용합니다.
func getTargetForRedirect(target string, domain string) string {
	// 입력 검증
	if target == "" || domain == "" {
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
		return "https://" + domain
	}

	// 도메인 내에 있는지 확인
	if isSameDomain(targetHost, domain) {
		// 같은 도메인인 경우 https 프로토콜을 보장하여 반환
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// 다른 도메인인 경우 도메인 URL 반환
	return "https://" + domain
}

// isSameDomain은 대상 호스트가 주어진 도메인 내에 있는지 확인합니다.
func isSameDomain(targetHost, domain string) bool {
	// 정확히 같은 도메인인 경우
	if targetHost == domain {
		return true
	}

	// 서브도메인인 경우 확인 (예: music.example.com은 example.com의 서브도메인)
	if strings.HasSuffix(targetHost, "."+domain) {
		return true
	}

	// www 접두사 처리 (www.example.com은 example.com과 동일하게 처리)
	if targetHost == "www."+domain || strings.HasSuffix(targetHost, ".www."+domain) {
		return true
	}

	return false
}