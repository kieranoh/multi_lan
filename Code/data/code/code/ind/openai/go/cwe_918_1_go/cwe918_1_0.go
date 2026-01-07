package main

import (
	"fmt"
	"net/url"
	"strings"
)

// getURLForQuery generates a query URL based on the given API URL and user ID.
// It returns nil if the user ID is empty or invalid.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	parsedURL, err := url.Parse(apiURL)
	if err != nil {
		return nil
	}

	// Append the user ID to the path
	parsedURL.Path = strings.TrimSuffix(parsedURL.Path, "/") + "/" + strings.TrimSpace(userID)

	result := parsedURL.String()
	return &result
}