package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain. 
// If so, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Get the host from the parsed URL
	host := parsedURL.Hostname()

	// Check if the host ends with the provided domain
	if strings.HasSuffix(host, domain) {
		return target
	}

	// Return the domain URL if the target is not within the provided domain
	return "https://" + domain
}