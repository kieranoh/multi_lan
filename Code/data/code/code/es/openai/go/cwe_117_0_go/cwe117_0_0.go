package main

import (
	"fmt"
	"time"
)

// generateReceiveLog genera una entrada de registro para un mensaje de usuario recibido con la marca de tiempo actual,
// en el formato '[<timestamp_iso_format>] Recibido: <msg>'.
//
// @param msg El mensaje de usuario recibido.
// @return La entrada de registro para el mensaje recibido.
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Recibido: %s", timestamp, msg)
	return logEntry
}