package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the provided domain.
// If so, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // fallback to domain on error
	}

	// Ensure the scheme is HTTPS
	if parsedTarget.Scheme != "https" {
		parsedTarget.Scheme = "https"
	}

	// Check if the host of the target URL contains the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return parsedTarget.String()
	}

	// Return the domain URL if the target is not in the domain
	return "https://" + domain
}