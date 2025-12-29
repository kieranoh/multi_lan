package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// If target is not a valid URL, redirect to the domain with https
		return "https://" + domain
	}

	// Ensure the target URL uses https
	targetURL.Scheme = "https"

	// Get the host from the parsed URL
	host := targetURL.Hostname()
	if host == "" {
		// If no host, redirect to the domain
		return "https://" + domain
	}

	// Check if the target host is within the domain
	// This handles exact matches and subdomains
	if host == domain || strings.HasSuffix(host, "."+domain) {
		// Return the target URL with https
		return targetURL.String()
	}

	// Otherwise, redirect to the domain with https
	return "https://" + domain
}