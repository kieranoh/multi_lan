package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL string is within the specified domain.
// If it is, it returns the target URL for redirection.
// Otherwise, it falls back to the redirect domain URL using HTTPS.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Extract the host from the parsed target URL
	targetHost := parsedTarget.Hostname()

	// Check if the host ends with the specified domain
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// Fallback to the domain URL
	return "https://" + domain
}