package main

import (
	"fmt"
	"time"
)

/* Luo lokimerkintä vastaanotetulle käyttäjäviestille nykyisellä aikaleimalla muodossa '[<timestamp_iso_format>] Vastaanotettu: <msg>'.

@param msg Vastaanotettu käyttäjäviesti.

@return Lokimerkintä vastaanotetulle viestille. */
func generateReceiveLog(msg string) string {
	// Haetaan nykyinen aika ISO 8601 -muodossa
	timestamp := time.Now().Format(time.RFC3339)
	
	// Muodostetaan lokimerkintä
	logEntry := fmt.Sprintf("[%s] Vastaanotettu: %s", timestamp, msg)
	
	return logEntry
}