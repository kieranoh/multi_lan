package main

import (
	"fmt"
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
	// 입력값 검증: 사용자 이름이 비어있는 경우 기본 메시지 반환
	if strings.TrimSpace(username) == "" {
		return "환영합니다, 게스트!"
	}
	
	// HTML 특수 문자 이스케이프 처리 (XSS 방지)
	escapedUsername := html.EscapeString(username)
	
	// 환영 메시지 생성
	welcomeMessage := fmt.Sprintf("환영합니다, %s!", escapedUsername)
	
	return welcomeMessage
}