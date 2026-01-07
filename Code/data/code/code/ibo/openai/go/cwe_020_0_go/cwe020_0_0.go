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
	parsedTarget, err := url.Parse(target)
	if err != nil || parsedTarget.Scheme != "https" {
		// If parsing fails or it's not HTTPS, return the domain with HTTPS
		return "https://" + domain
	}

	// Check if the host of the target URL contains the domain
	if strings.Contains(parsedTarget.Hostname(), domain) {
		return target
	}

	// If the domain is not matched, return the domain URL with HTTPS
	return "https://" + domain
}