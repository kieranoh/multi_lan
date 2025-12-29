package main

import (
	"fmt"
	"time"
)

// generateReceiveLog generates a log entry for a received user message with the current timestamp
// in the format '[<timestamp_iso_format>] Received: <msg>'.
// 
// @param msg Received user message.
// @return Log entry for the received message.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Odebrano: %s", currentTime, msg)
}