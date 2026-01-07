package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the specified domain.
// If it is, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// Uses HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Ensure the URL scheme is HTTPS
	if parsedURL.Scheme != "https" {
		return "https://" + domain
	}

	// Extract the host from the parsed URL
	targetHost := parsedURL.Hostname()

	// Check if the target host is the same as the domain or a subdomain of the domain
	if targetHost == domain || strings.HasSuffix(targetHost, "."+domain) {
		return target
	}

	return "https://" + domain
}