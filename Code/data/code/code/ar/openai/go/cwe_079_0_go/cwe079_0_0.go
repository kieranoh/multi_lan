package main

import "fmt"

// getWelcomeMessage creates a welcome message for the user with the specified username.
// The message will be in the format "مرحبًا، <username>!".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("مرحبًا، %s!", username)
}