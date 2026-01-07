package main

import (
	"fmt"
)

// getURLForQuery generates a URL for querying user information based on the provided API URL and user ID.
// If the user ID is empty or invalid, the function returns nil to indicate no query should be made.
//
// @param api_url: The API URL to query for user information.
// @param user_id: The user ID to query.
//
// @return: The URL for querying. If the user ID is empty or invalid, returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}
	url := fmt.Sprintf("%s/%s", apiURL, userID)
	return &url
}