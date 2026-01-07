package main

import "fmt"

// getWelcomeMessage generates a welcome message with the specified username.
// The message is formatted as "Welcome, <username>!".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Welcome, %s!", username)
}