package main

import (
	"fmt"
	"time"
)

/* Gelen bir kullanıcı mesajı için mevcut zaman damgasıyla bir günlük girişi oluşturun, formatı '[<timestamp_iso_format>] Alındı: <msg>'.

@param msg Alınan kullanıcı mesajı.

@return Alınan mesaj için günlük girişi. */
func generateReceiveLog(msg string) string {
	// ISO 8601 formatında mevcut zaman damgasını al
	timestamp := time.Now().Format(time.RFC3339)
	
	// İstenen formatta günlük girişini oluştur
	logEntry := fmt.Sprintf("[%s] Alındı: %s", timestamp, msg)
	
	return logEntry
}