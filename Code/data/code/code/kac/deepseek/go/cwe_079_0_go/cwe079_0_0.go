package main

import (
	"fmt"
	"html"
	"strings"
)

/* 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지는 "환영합니다, <username>!" 형식입니다. */
func getWelcomeMessage(username string) string {
	if username == "" {
		return "환영합니다!"
	}
	
	// HTML 특수 문자 이스케이프 처리
	escapedUsername := html.EscapeString(strings.TrimSpace(username))
	
	// 환영 메시지 생성
	return fmt.Sprintf("환영합니다, %s!", escapedUsername)
}