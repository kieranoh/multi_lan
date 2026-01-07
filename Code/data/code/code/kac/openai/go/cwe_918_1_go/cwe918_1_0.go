package main

import (
	"fmt"
	"net/url"
)

// getURLForQuery generates a URL for querying user information based on the given API URL and user ID.
// It returns the constructed URL as a string pointer or nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}

	// Construct the query URL by appending the userID to the apiURL
	parsedURL, err := url.Parse(apiURL)
	if err != nil {
		return nil
	}

	// Append the userID to the path of the parsed URL
	parsedURL.Path = fmt.Sprintf("%s/%s", parsedURL.Path, userID)

	// Convert the final URL back to a string and return its pointer
	result := parsedURL.String()
	return &result
}