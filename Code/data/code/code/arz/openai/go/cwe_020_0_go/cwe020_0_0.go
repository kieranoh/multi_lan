package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If it is, returns the target URL for redirection; otherwise, returns the domain URL for redirection.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the host of the target URL ends with the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	// Return the domain URL with HTTPS
	return "https://" + domain
}