package main

import (
	"fmt"
	"time"
)

// generateReceiveLog создает запись в журнале для полученного сообщения пользователя с текущей меткой времени в формате '[<timestamp_iso_format>] Получено: <msg>'.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Получено: %s", currentTime, msg)
}