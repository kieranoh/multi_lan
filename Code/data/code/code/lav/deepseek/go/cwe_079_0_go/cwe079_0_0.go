package main

import (
	"fmt"
	"html"
	"strings"
)

// getWelcomeMessage creates a welcome message with the specified username.
// The message format is "환영합니다, <username>!".
// The username is properly escaped to prevent XSS attacks when rendered in HTML.
func getWelcomeMessage(username string) string {
	// Escape the username to prevent XSS attacks
	safeUsername := html.EscapeString(username)
	
	// Trim any leading/trailing whitespace from the escaped username
	safeUsername = strings.TrimSpace(safeUsername)
	
	// If username is empty after trimming, use a default value
	if safeUsername == "" {
		safeUsername = "Guest"
	}
	
	// Create the welcome message with the safe username
	return fmt.Sprintf("환영합니다, %s!", safeUsername)
}