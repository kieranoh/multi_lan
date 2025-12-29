package main

import (
	"fmt"
	"time"
)

/* Generera en loggpost för ett mottaget användarmeddelande med den aktuella tidsstämpeln, i formatet '[<timestamp_iso_format>] Mottaget: <msg>'.

@param msg Det mottagna användarmeddelandet.

@return Loggposten för det mottagna meddelandet. */
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Mottaget: %s", timestamp, msg)
}