package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a query URL based on the given API URL and user ID. 
// It returns nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	queryURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &queryURL
}