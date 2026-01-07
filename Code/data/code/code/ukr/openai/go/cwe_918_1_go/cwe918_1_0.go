package main

import (
	"strings"
)

// getURLForQuery generates a query URL based on the provided API URL and user ID.
// It returns nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	queryURL := apiURL + "/" + userID
	return &queryURL
}