package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If it is, it returns the target URL for redirection, otherwise it replaces it with the domain URL.
// The function uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // Return the domain if the URL is invalid
	}

	// Check if the host of the target URL contains the domain
	if strings.Contains(parsedURL.Host, domain) {
		return target // Return the original URL if it's within the domain
	}

	// If not, return the domain URL with the HTTPS protocol
	return "https://" + domain
}