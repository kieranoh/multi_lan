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

	// Ensure the target URL has a host
	if targetURL.Host == "" {
		return "https://" + domain
	}

	// Check if the target host is within the specified domain
	if isWithinDomain(targetURL.Host, domain) {
		// Ensure the returned URL uses https
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// If not within domain, return the domain with https
	return "https://" + domain
}

// Helper function to check if a host is within a domain
func isWithinDomain(host, domain string) bool {
	// Remove port if present
	hostWithoutPort := strings.Split(host, ":")[0]
	
	// Check exact match
	if hostWithoutPort == domain {
		return true
	}
	
	// Check subdomain match
	return strings.HasSuffix(hostWithoutPort, "."+domain)
}