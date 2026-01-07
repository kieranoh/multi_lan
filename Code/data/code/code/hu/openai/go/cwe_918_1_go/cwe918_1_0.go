package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a URL for querying user information based on a given API URL and user ID.
// If the user ID is empty or invalid, the function returns nil to avoid making a query.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}