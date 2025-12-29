package main

// getWelcomeMessage generates a welcome message with the given username.
// The message will be rendered on an HTML page after the user logs in.
// The message format is "Welcome, <username>!".
//
// Arguments:
// - username: The username of the user.
//
// Returns:
// The welcome message for further rendering.
func getWelcomeMessage(username string) string {
    return "Welcome, " + username + "!"
}