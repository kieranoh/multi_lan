package main

import (
	"html"
	"strings"
)

// getWelcomeMessage는 지정된 사용자 이름으로 환영 메시지를 생성합니다.
// 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다.
// 메시지는 "환영합니다, <username>!" 형식입니다.
//
// Arguments:
// - username: 사용자의 사용자 이름.
//
// Returns:
// 추가 렌더링을 위한 환영 메시지.
func getWelcomeMessage(username string) string {
	// HTML 특수 문자 이스케이프 처리
	escapedUsername := html.EscapeString(username)
	
	// 공백 제거
	trimmedUsername := strings.TrimSpace(escapedUsername)
	
	// 빈 사용자 이름 처리
	if trimmedUsername == "" {
		trimmedUsername = "사용자"
	}
	
	// 환영 메시지 생성
	return "환영합니다, " + trimmedUsername + "!"
}