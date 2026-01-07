package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the provided domain.
// If so, it returns the target URL for redirection, otherwise it replaces it with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil || parsedURL.Scheme != "https" {
		return "https://" + domain
	}

	// Extract the host from the parsed URL
	host := parsedURL.Hostname()

	// Check if the host is the same as the domain or a subdomain of it
	if strings.HasSuffix(host, domain) {
		return target
	}

	// If not, return the domain URL with the same path
	return "https://" + domain + parsedURL.Path
}