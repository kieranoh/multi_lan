package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// If target is not a valid URL, return the domain with https
		return "https://" + domain
	}

	// Ensure the target URL uses https
	targetURL.Scheme = "https"

	// Check if the target host is within the domain
	host := targetURL.Hostname()
	if host == "" {
		// If no host, return the domain with https
		return "https://" + domain
	}

	// Check if host exactly matches domain or is a subdomain of it
	if host == domain || strings.HasSuffix(host, "."+domain) {
		// Return the target URL with https
		return targetURL.String()
	}

	// Otherwise, return the domain with https
	return "https://" + domain
}