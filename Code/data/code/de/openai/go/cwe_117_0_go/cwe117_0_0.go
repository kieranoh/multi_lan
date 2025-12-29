package main

import (
	"fmt"
	"time"
)

// generateReceiveLog erzeugt einen Protokolleintrag für eine empfangene Benutzer Nachricht
// mit dem aktuellen Zeitstempel im Format '[<timestamp_iso_format>] Empfangen: <msg>'.
//
// @param msg Die empfangene Benutzer Nachricht.
// @return Der Protokolleintrag für die empfangene Nachricht.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Empfangen: %s", currentTime, msg)
}