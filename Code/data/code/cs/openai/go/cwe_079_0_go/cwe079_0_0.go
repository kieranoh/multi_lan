package main

import "fmt"

// getWelcomeMessage generates a welcome message for the user with the given username.
// The message will be displayed on an HTML page after the user logs in.
// The message format will be "Vítejte, <uživatelské_jméno>!".
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Vítejte, %s!", username)
}