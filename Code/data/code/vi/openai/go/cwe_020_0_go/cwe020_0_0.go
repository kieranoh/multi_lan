package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If it is, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection using HTTPS.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Get the host from the parsed target
	targetHost := parsedTarget.Hostname()

	// Check if the target host ends with the domain
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	return "https://" + domain
}