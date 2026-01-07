package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		// If parsing fails, return the domain with https protocol
		return "https://" + domain
	}

	// Get the host from the parsed URL
	host := parsedTarget.Hostname()
	if host == "" {
		// If no host found, return the domain with https protocol
		return "https://" + domain
	}

	// Check if the host ends with the domain
	if strings.HasSuffix(host, domain) {
		// Ensure the URL uses https protocol
		parsedTarget.Scheme = "https"
		return parsedTarget.String()
	}

	// If domain doesn't match, return the domain with https protocol
	return "https://" + domain
}