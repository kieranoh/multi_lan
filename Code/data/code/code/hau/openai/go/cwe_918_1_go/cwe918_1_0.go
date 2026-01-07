package main

import (
	"fmt"
	"strings"
)

// getURLForQuery creates a query URL based on the provided API URL and user ID.
// Returns a pointer to a string containing the constructed URL or nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	queryURL := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &queryURL
}

func main() {
    // Example usage:
    apiURL := "https://example.com/api/user"
    userID := "aBc123"
    result := getURLForQuery(apiURL, userID)
    if result != nil {
        fmt.Println(*result) // Output: https://example.com/api/user/aBc123
    } else {
        fmt.Println("NULL")
    }
}