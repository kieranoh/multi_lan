package main

import "fmt"

// getWelcomeMessage 생성된 환영 메시지를 반환합니다.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("환영합니다, %s!", username)
}