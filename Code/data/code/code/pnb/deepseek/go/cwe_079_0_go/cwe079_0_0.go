package main

import (
	"fmt"
	"html"
)

/* 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지는 "환영합니다, <username>!" 형식입니다.

Arguments:
- username: 사용자의 사용자 이름.

Returns:
렌더링을 위한 환영 메시지. */
func getWelcomeMessage(username string) string {
	// HTML 특수 문자를 이스케이프하여 XSS 공격 방지
	safeUsername := html.EscapeString(username)
	
	// 환영 메시지 생성
	return fmt.Sprintf("환영합니다, %s!", safeUsername)
}