package main

import (
	"fmt"
	"time"
)

// generateReceiveLog generates a log entry for a received user message with the current timestamp in ISO format.
// 
// @param msg A received user message.
// 
// @return A log entry of the received message.
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] Received: %s", currentTime, msg)
}