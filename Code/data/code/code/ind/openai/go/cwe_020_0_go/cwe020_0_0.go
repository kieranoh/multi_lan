package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL string is within the provided domain.
// If it is, it returns the target URL for redirection, otherwise it replaces it with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the host of the target contains the domain
	if strings.Contains(parsedTarget.Hostname(), domain) {
		return target
	}

	// If not, return the domain URL
	return "https://" + domain
}