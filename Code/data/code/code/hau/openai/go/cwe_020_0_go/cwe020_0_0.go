package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the provided domain.
// If so, it returns the target URL for redirection; otherwise, it replaces it with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// If parsing fails, return the domain as a fallback
		return "https://" + domain
	}

	// Ensure the target URL uses HTTPS
	if parsedTarget.Scheme != "https" {
		return "https://" + domain
	}

	// Extract the host from the parsed target
	targetHost := parsedTarget.Hostname()

	// Check if the target host is the same as the provided domain or a subdomain of it
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		return target // Return the original target URL for redirection
	}

	// If not, return the domain URL
	return "https://" + domain
}