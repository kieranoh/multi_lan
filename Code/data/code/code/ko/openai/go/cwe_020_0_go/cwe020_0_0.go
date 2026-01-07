package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL string is within the provided domain.
// If it is, returns the target URL for redirection; otherwise, returns the domain URL for redirection using HTTPS.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the target host ends with the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	// If not, return the domain URL
	return "https://" + domain
}