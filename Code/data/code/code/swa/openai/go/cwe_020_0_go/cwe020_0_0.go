package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If so, it returns the target URL for redirection; otherwise, it substitutes with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // Return domain URL if there is an error in parsing
	}

	// Check if the host of the target URL contains the domain
	if strings.Contains(parsedURL.Host, domain) {
		return target // Return the target URL if it contains the domain
	}

	// Return the domain URL if not contained
	return "https://" + domain
}