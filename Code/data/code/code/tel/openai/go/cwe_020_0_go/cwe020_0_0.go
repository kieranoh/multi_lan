package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given target URL is within the provided domain.
// If it is, it returns the target URL for redirection, otherwise it replaces it with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Ensure the scheme is HTTPS
	if parsedTarget.Scheme != "https" {
		parsedTarget.Scheme = "https"
	}

	// Check if the host of the target contains the provided domain
	if strings.Contains(parsedTarget.Host, domain) {
		return parsedTarget.String()
	}

	// If not, return the domain URL
	return "https://" + domain
}