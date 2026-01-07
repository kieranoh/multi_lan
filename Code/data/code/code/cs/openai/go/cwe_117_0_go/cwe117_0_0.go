package main

import (
	"fmt"
	"time"
)

// generateReceiveLog vygeneruje záznam do protokolu pro přijatou uživatelskou zprávu s aktuálním časovým razítkem ve formátu '[<timestamp_iso_format>] Přijato: <msg>'.
//
// @param msg Přijatá uživatelská zpráva.
//
// @return Záznam do protokolu pro přijatou zprávu.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Přijato: %s", currentTime, msg)
}