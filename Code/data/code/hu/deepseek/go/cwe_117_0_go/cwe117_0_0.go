package main

import (
	"fmt"
	"time"
)

/* Generálj egy naplóbejegyzést egy beérkezett felhasználói üzenetről a jelenlegi időbélyeggel, a következő formátumban: '[<timestamp_iso_format>] Received: <msg>'.

@param msg A beérkezett felhasználói üzenet.

@return A beérkezett üzenet naplóbejegyzése. */
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Received: %s", timestamp, msg)
}