package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a query URL based on the provided API URL and user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}