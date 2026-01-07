package main

import (
	"fmt"
	"time"
)

// generateReceiveLog는 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 생성합니다.
// 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다.
//
// @param msg 수신된 사용자 메시지입니다.
// @return 수신된 메시지에 대한 로그 항목입니다.
func generateReceiveLog(msg string) string {
	// 현재 시간을 ISO 8601 형식으로 포맷팅
	timestamp := time.Now().Format(time.RFC3339)
	
	// 로그 항목 생성
	logEntry := fmt.Sprintf("[%s] 수신됨: %s", timestamp, msg)
	
	return logEntry
}