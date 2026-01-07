package main

// getWelcomeMessage generates a welcome message with the given username.
// The message is formatted as "Welcome, <username>!" for rendering after user login.
func getWelcomeMessage(username string) string {
    return "Welcome, " + username + "!"
}