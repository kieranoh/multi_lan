package main

import (
	"fmt"
)

// getWelcomeMessage generates a welcome message using the provided username.
// The message is in the format "Welcome, <username>!".
func getWelcomeMessage(username string) string {
	return fmt.Sprintf("Welcome, %s!", username)
}

func main() {
	// Example usage
	username := "JohnDoe"
	message := getWelcomeMessage(username)
	fmt.Println(message) // This line is just for demonstration and should not be executed directly.
}