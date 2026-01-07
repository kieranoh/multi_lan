package main

import (
	"fmt"
	"time"
)

/* Sartu erabiltzailearen mezu bat jaso den log irteera, unean unean, formatuan '[<timestamp_iso_format>] Jasotakoa: <msg>'.

@param msg Jasotako erabiltzaile mezu.

@return Jasotako mezuaren log irteera. */
func generateReceiveLog(msg string) string {
	timestamp := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Jasotakoa: %s", timestamp, msg)
}