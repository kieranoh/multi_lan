package main

import (
	"net/url"
)

// getURLForQuery generates a URL for querying user information based on the given API URL and user ID.
// If the user ID is empty or invalid, it returns nil.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}

	parsedURL, err := url.Parse(apiURL)
	if err != nil {
		return nil
	}

	// Append userID to the path of the URL
	parsedURL.Path = url.JoinPath(parsedURL.Path, userID)

	result := parsedURL.String()
	return &result
}