package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a query URL based on the given API URL and user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	queryURL := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &queryURL
}