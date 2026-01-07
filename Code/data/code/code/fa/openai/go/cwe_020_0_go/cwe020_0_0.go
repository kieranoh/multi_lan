package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks whether the provided target URL is within the given domain.
// If so, it returns the target URL for redirection; otherwise, it returns the domain URL for redirection.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // fallback to domain if parsing fails
	}

	// Ensure the scheme is HTTPS
	if parsedTarget.Scheme != "https" {
		return "https://" + domain // fallback to domain if the scheme is not HTTPS
	}

	// Check if the host of the target URL contains the domain
	if strings.Contains(parsedTarget.Host, domain) {
		return target // return the target URL if it is within the domain
	}

	// If not, return the domain URL
	return "https://" + domain
}