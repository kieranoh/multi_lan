package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a URL for querying user information based on the provided API URL and user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	url := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &url
}

func main() {
	// Example usage:
	queryURL1 := getURLForQuery("https://example.com/api/user", "aBc123")
	if queryURL1 != nil {
		fmt.Println(*queryURL1) // Output: https://example.com/api/user/aBc123
	} else {
		fmt.Println("NULL")
	}

	queryURL2 := getURLForQuery("https://example.com/api/user", "")
	if queryURL2 != nil {
		fmt.Println(*queryURL2)
	} else {
		fmt.Println("NULL") // Output: NULL
	}
}