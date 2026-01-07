package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL belongs to the specified domain.
// If it does, it returns the target URL for redirection; otherwise, it replaces it with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the host contains the domain
	if strings.Contains(parsedURL.Host, domain) {
		return target
	}

	// If not, return the domain URL with HTTPS
	return "https://" + domain
}