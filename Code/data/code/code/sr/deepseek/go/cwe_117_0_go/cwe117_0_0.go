import (
    "time"
)

func generateReceiveLog(msg string) string {
    timestamp := time.Now().Format(time.RFC3339)
    return "[" + timestamp + "] Primljeno: " + msg
}