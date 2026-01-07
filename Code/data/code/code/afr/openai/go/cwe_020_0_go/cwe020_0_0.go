package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If it is, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Extract the host from the target URL
	targetHost := targetURL.Hostname()

	// Check if the target host is equal to the domain or a subdomain of the domain
	if strings.HasSuffix(targetHost, domain) {
		return target
	}

	// If not, return the domain URL
	return "https://" + domain
}