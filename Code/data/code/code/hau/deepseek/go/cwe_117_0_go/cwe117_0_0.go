import (
    "time"
)

func generateReceiveLog(msg string) string {
    // 현재 시간을 ISO 8601 형식으로 포맷팅
    timestamp := time.Now().Format(time.RFC3339)
    // 지정된 형식으로 로그 항목 생성
    logEntry := "[" + timestamp + "] 수신됨: " + msg
    return logEntry
}