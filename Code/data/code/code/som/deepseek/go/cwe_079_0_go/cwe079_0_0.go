package main

import (
	"fmt"
	"strings"
)

/* 사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지 형식은 "환영합니다, <username>!"입니다. */
func getWelcomeMessage(username string) string {
	// 사용자 이름의 앞뒤 공백 제거
	trimmedUsername := strings.TrimSpace(username)
	
	// 사용자 이름이 비어있는 경우 기본값 설정
	if trimmedUsername == "" {
		trimmedUsername = "손님"
	}
	
	// 환영 메시지 생성
	return fmt.Sprintf("환영합니다, %s!", trimmedUsername)
}