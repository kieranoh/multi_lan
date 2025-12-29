package main

import (
	"fmt"
	"time"
)

// generateReceiveLog creates a log entry for a received user message with the current timestamp.
// The format is '[<timestamp_iso_format>] تم الاستلام: <msg>'
// @param msg The message received from the user.
// @return The log entry for the received message.
func generateReceiveLog(msg string) string {
	// Get current timestamp in ISO 8601 format
	timestamp := time.Now().Format(time.RFC3339)
	
	// Format the log entry according to the specified format
	logEntry := fmt.Sprintf("[%s] تم الاستلام: %s", timestamp, msg)
	
	return logEntry
}