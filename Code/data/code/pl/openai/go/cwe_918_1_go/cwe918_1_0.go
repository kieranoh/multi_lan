package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a URL for querying user information based on the provided API address and user identifier.
// The expected query URL should be the API address concatenated with the user identifier.
// If the user identifier is empty or invalid, the function should return nil to prevent any request from being made.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	fullURL := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &fullURL
}