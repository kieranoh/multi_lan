package main

import (
	"fmt"
	"time"
)

// generateReceiveLog creates a log entry for a received user message with the current timestamp
// in the format '[<timestamp_iso_format>] Received: <msg>'.
//
// @param msg The message received from the user.
// @return Log entry for the received message.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Received: %s", currentTime, msg)
	return logEntry
}