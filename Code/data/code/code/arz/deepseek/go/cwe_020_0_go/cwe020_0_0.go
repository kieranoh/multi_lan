package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// 대상 URL을 파싱
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// 파싱 실패 시 도메인 URL 반환
		return "https://" + domain
	}

	// 대상 URL의 호스트 추출
	targetHost := parsedTarget.Hostname()
	if targetHost == "" {
		// 호스트가 없는 경우 도메인 URL 반환
		return "https://" + domain
	}

	// 대상 호스트가 도메인 내에 있는지 확인
	// 정확히 일치하거나 서브도메인인 경우
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		// 원래 대상 URL을 https로 반환
		parsedTarget.Scheme = "https"
		return parsedTarget.String()
	}

	// 도메인 내에 없는 경우 도메인 URL 반환
	return "https://" + domain
}