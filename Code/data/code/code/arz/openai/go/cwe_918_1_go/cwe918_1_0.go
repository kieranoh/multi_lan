package main

import (
	"fmt"
	"net/url"
)

// getURLForQuery generates a URL for querying user information based on the provided API URL and user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	// Check if the user ID is empty
	if userID == "" {
		return nil
	}

	// Parse the API URL
	parsedURL, err := url.Parse(apiURL)
	if err != nil {
		return nil
	}

	// Append the user ID to the path
	parsedURL.Path = fmt.Sprintf("%s/%s", parsedURL.Path, userID)

	// Convert the updated URL back to string and return as a pointer
	result := parsedURL.String()
	return &result
}