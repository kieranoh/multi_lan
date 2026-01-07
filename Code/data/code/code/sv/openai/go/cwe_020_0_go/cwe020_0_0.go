package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given target address is within the specified domain.
// If so, it returns the target address for redirection; otherwise, it returns the domain address for redirection.
// It uses the https protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Ensure the target uses the https protocol
	if parsedTarget.Scheme != "https" {
		return "https://" + domain
	}

	// Check if the target host contains the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	// Return the domain address for redirection
	return "https://" + domain
}