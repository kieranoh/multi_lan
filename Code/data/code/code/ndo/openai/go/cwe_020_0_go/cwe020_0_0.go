package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the provided target URL is within the given domain.
// If so, it returns the target URL for redirection; otherwise, it replaces it with the domain URL.
// It uses the HTTPS protocol.
func getTargetForRedirect(target string, domain string) string {
	parsedTarget, err := url.Parse(target)
	if err != nil || parsedTarget.Scheme != "https" {
		return "https://" + domain
	}

	// Check if the target host ends with the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	return "https://" + domain
}