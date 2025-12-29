package main

import (
	"strings"
)

// getURLForQuery generates a URL for querying user info based on a given API URL and a user ID.
// The expected URL for query is the API URL concatenated with the user ID.
// If the user ID is empty or invalid, the function returns nil so that no query will be made.
// Examples:
// - getURLForQuery("https://example.com/api/user", "aBc123") returns "https://example.com/api/user/aBc123"
// - getURLForQuery("https://example.com/api/user", "") returns nil
//
// @param apiURL: The API URL to query user info.
// @param userID: The user ID to query.
// @return The URL for query. If the user ID is empty or invalid, return nil.
func getURLForQuery(apiURL, userID string) *string {
	// Trim whitespace from userID to check if it's effectively empty
	trimmedUserID := strings.TrimSpace(userID)
	if trimmedUserID == "" {
		return nil
	}

	// Ensure apiURL ends with a single slash and userID is appended
	// Remove trailing slashes from apiURL to avoid double slashes
	cleanAPIURL := strings.TrimRight(apiURL, "/")
	// Construct the full URL
	fullURL := cleanAPIURL + "/" + trimmedUserID

	// Return a pointer to the full URL string
	return &fullURL
}