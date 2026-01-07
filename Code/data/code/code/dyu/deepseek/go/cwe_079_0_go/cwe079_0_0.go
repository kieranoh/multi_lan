package main

import (
	"fmt"
	"html"
	"strings"
)

/* 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지는 "환영합니다, <username>!" 형식입니다. */
func getWelcomeMessage(username string) string {
	if strings.TrimSpace(username) == "" {
		return "환영합니다!"
	}
	
	// HTML 인코딩을 통해 XSS 공격 방지
	safeUsername := html.EscapeString(username)
	
	return fmt.Sprintf("환영합니다, %s!", safeUsername)
}