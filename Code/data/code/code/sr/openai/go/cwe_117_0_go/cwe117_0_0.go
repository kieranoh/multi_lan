package main

import (
	"fmt"
	"time"
)

// generateReceiveLog generiše zapis u dnevniku za primljenu korisničku poruku
// sa trenutnim vremenskim pečatom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
//
// @param msg Primljena korisnička poruka.
//
// @return Zapis u dnevniku za primljenu poruku.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Primljeno: %s", currentTime, msg)
	return logEntry
}