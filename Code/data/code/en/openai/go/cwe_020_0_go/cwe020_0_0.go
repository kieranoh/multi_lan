package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL string is within the provided domain.
// If so, it returns the target URL for redirect; otherwise, it falls back to the domain URL for redirect.
// The function uses https protocol for the returned URL.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // Return fallback domain if parsing fails
	}

	// Ensure we are using https protocol
	if parsedURL.Scheme != "https" {
		parsedURL.Scheme = "https"
	}

	// Check if the target URL is within the provided domain
	if strings.HasSuffix(parsedURL.Hostname(), domain) {
		return parsedURL.String()
	}

	// Fallback to the domain URL
	return "https://" + domain
}