package main

import "fmt"

// getWelcomeMessage generates a welcome message for the user with the specified username.
// This message will be displayed on the HTML page after the user logs in.
// The message will be in the format "Welcome, <username>!".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Witaj, %s!", username)
}