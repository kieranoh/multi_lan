package main

import "fmt"

// getWelcomeMessage generates a welcome message with the provided username.
// The message is formatted as "Welcome, <username>!" for rendering on an HTML page.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Welcome, %s!", username)
}