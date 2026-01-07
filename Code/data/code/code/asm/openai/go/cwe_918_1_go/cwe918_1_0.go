package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a URL for querying user information based on the given API URL and user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	fullURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &fullURL
}