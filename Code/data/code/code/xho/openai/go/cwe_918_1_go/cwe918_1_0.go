package main

import (
	"fmt"
)

// getURLForQuery generates a query URL for user information based on the provided API URL and user ID.
// If the user ID is empty or invalid, the function returns nil to indicate that no query should be made.
//
// @param api_url: The API URL for querying user information.
// @param user_id: The user ID to query.
//
// @return: A string pointer to the query URL. Returns nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}