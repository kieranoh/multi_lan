package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given target URL is within the specified domain.
// If it is, it returns the target URL for redirection; otherwise, it redirects to the domain URL.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // Fallback to the domain if parsing fails
	}

	// Ensure the target URL uses HTTPS
	if parsedTarget.Scheme != "https" {
		return "https://" + domain // Fallback if not HTTPS
	}

	// Check if the target host ends with the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target // Return the target URL if it's within the domain
	}

	// Redirect to the domain
	return "https://" + domain
}