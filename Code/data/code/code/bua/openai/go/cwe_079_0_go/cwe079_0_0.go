package main

// getWelcomeMessage generates a welcome message for the given username.
// The message will be rendered on an HTML page after the user logs in.
// The format of the message is "Welcome, <username>!".
func getWelcomeMessage(username string) string {
    return "Welcome, " + username + "!"
}