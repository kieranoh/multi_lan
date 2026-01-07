package main

import "fmt"

// getWelcomeMessage generates a welcome message using the provided username.
// The message format is: "Welcome, <username>!".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Üdvözöljük, %s!", username)
}