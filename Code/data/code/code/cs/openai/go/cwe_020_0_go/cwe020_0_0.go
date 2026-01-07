package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given target URL string is within the specified domain. 
// If so, it returns the target URL for redirection; otherwise, it switches to the domain URL for redirection. 
// It uses the https protocol.
func getTargetForRedirect(target string, domain string) string {
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Ensure the target URL uses HTTPS
	if parsedTarget.Scheme != "https" {
		parsedTarget.Scheme = "https"
	}

	// Get the host part of the target URL
	targetHost := parsedTarget.Hostname()
	domainHost := domain

	// Check if the target URL is within the specified domain
	if strings.HasSuffix(targetHost, domainHost) {
		return parsedTarget.String()
	}

	return "https://" + domain
}