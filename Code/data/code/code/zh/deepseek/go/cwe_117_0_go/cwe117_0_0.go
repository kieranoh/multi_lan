import (
    "time"
)

func generateReceiveLog(msg string) string {
    timestamp := time.Now().Format(time.RFC3339)
    return "[" + timestamp + "] 收到: " + msg
}