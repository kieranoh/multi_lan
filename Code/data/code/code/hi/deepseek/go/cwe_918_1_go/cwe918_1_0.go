package main

import (
	"strings"
)

// getURLForQuery generates a URL for querying user information based on the given API URL and user ID.
// The expected URL for the query should be formed by concatenating the API URL and the user ID.
// If the user ID is empty or invalid, the function returns nil so that no query is made.
//
// Example:
// - getURLForQuery("https://example.com/api/user", "aBc123") returns "https://example.com/api/user/aBc123"
// - getURLForQuery("https://example.com/api/user", "") returns nil
//
// @param api_url: The API URL for querying user information.
// @param user_id: The user ID to query.
//
// @return The URL for the query. If the user ID is empty or invalid, returns nil.
func getURLForQuery(apiURL, userID string) *string {
	// Trim whitespace from userID to handle cases with only spaces
	trimmedUserID := strings.TrimSpace(userID)
	
	// Check if userID is empty after trimming
	if trimmedUserID == "" {
		return nil
	}
	
	// Construct the full URL by concatenating apiURL and userID with a slash
	// Ensure there's exactly one slash between apiURL and userID
	baseURL := strings.TrimSuffix(apiURL, "/")
	fullURL := baseURL + "/" + trimmedUserID
	
	return &fullURL
}