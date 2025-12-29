package main

import (
	"fmt"
	"time"
)

// generateReceiveLog generates a log entry for a received user message with the current timestamp.
// The log entry is in the format '[<timestamp_iso_format>] Received: <msg>'.
//
// @param msg The user message received.
// @return The log entry for the received message.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	logEntry := fmt.Sprintf("[%s] Received: %s", currentTime, msg)
	return logEntry
}