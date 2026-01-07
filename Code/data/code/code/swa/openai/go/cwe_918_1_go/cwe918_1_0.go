package main

import (
	"fmt"
	"strings"
)

// getURLForQuery creates a URL for querying user information based on the given API URL and user ID.
// It returns a pointer to a string containing the constructed URL, or nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &queryURL
}