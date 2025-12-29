package main

// getWelcomeMessage generates a welcome message for the user with the given username.
// The message will be displayed on an HTML page after the user has logged in.
// The message will be in the format "Welcome, <username>!".
func getWelcomeMessage(username string) string {
    return "Välkommen, " + username + "!"
}