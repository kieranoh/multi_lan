package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given target URL string is within the provided domain.
// If yes, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// It uses HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Get the host from the target URL
	targetHost := parsedTarget.Hostname()

	// Check if the target host contains the domain
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// Return the domain URL if not matched
	return "https://" + domain
}