package main

import "fmt"

// getWelcomeMessage generates a welcome message with the specified username.
// The message will be rendered on an HTML page after the user logs in.
// The format of the message is "Welcome, <username>!".
//
// Arguments:
// - username: the user's username.
//
// Returns:
// A welcome message for further rendering.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Welcome, %s!", username)
}