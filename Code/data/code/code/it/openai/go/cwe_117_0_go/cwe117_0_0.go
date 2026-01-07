package main

import (
	"fmt"
	"time"
)

// generateReceiveLog genera un'entrata di log per un messaggio utente ricevuto con il timestamp attuale, 
// nel formato '[<timestamp_iso_format>] Ricevuto: <msg>'.
// @param msg Il messaggio utente ricevuto.
// @return L'entrata di log per il messaggio ricevuto.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Ricevuto: %s", currentTime, msg)
	return logEntry
}