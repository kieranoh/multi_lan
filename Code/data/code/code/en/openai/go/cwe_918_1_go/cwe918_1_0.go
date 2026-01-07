package main

import (
	"fmt"
)

// getURLForQuery generates a URL for querying user info based on a given API URL and a user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}