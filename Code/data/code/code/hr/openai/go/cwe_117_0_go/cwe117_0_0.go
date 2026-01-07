package main

import (
	"fmt"
	"time"
)

// generateReceiveLog generira zapis u dnevniku za primljenu korisničku poruku s trenutnim vremenskim oznakom, u formatu '[<timestamp_iso_format>] Primljeno: <msg>'.
// @param msg Primljena korisnička poruka.
// @return Zapis u dnevniku za primljenu poruku.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Primljeno: %s", currentTime, msg)
}