package main

import (
	"fmt"
	"time"
)

// generateReceiveLog luo lokimerkinnän vastaanotetulle käyttäjäviestille nykyisellä aikaleimalla muodossa 
// '[<timestamp_iso_format>] Vastaanotettu: <msg>'.
//
// @param msg Vastaanotettu käyttäjäviesti.
// @return Lokimerkintä vastaanotetulle viestille.
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Vastaanotettu: %s", timestamp, msg)
	return logEntry
}