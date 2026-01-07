package main

import (
	"fmt"
	"time"
)

// generateReceiveLog создает запись в журнале для полученного сообщения пользователя
// с текущей меткой времени в формате '[<timestamp_iso_format>] Получено: <msg>'
// @param msg Полученное сообщение пользователя
// @return Запись в журнале для полученного сообщения
func generateReceiveLog(msg string) string {
	// Получаем текущее время в формате ISO 8601 (RFC3339)
	timestamp := time.Now().Format(time.RFC3339)
	
	// Форматируем строку журнала согласно требуемому формату
	logEntry := fmt.Sprintf("[%s] Получено: %s", timestamp, msg)
	
	return logEntry
}