package main

import (
	"fmt"
	"strings"
)

// getURLForQuery creates a user info query URL based on the given API URL and user ID.
// If the user ID is empty or invalid, it returns nil to avoid making any query.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &queryURL
}