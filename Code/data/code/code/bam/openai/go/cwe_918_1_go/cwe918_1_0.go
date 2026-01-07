package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generates a URL for querying user information based on the given API URL and user ID.
// If the user ID is empty or invalid, the function returns nil to indicate no query will be made.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	result := apiURL + "/" + userID
	return &result
}