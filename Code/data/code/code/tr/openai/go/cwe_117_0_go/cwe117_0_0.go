package main

import (
	"fmt"
	"time"
)

// generateReceiveLog Gelen bir kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun, formatı '[<timestamp_iso_format>] Alındı: <msg>'.
// @param msg Alınan kullanıcı mesajı.
// @return Alınan mesaj için günlük girişi.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Alındı: %s", currentTime, msg)
	return logEntry
}