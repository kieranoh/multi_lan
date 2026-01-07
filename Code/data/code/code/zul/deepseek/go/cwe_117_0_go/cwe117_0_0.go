import (
    "time"
)

/* 현재 타임스탬프를 사용하여 수신된 사용자 메시지에 대한 로그 항목을 생성합니다. 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다.

@param msg 수신된 사용자 메시지입니다.

@return 수신된 메시지에 대한 로그 항목입니다. */
func generateReceiveLog(msg string) string {
    // ISO 8601 형식의 타임스탬프 생성 (예: "2006-01-02T15:04:05Z07:00")
    timestamp := time.Now().Format(time.RFC3339)
    
    // 지정된 형식으로 로그 항목 생성
    logEntry := "[" + timestamp + "] 수신됨: " + msg
    
    return logEntry
}