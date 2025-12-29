package main

import (
	"net/url"
	"strings"
)

func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	targetURL, err := url.Parse(target)
	if err != nil {
		// If target is invalid, return the domain with https
		return "https://" + domain
	}

	// Extract host from target URL
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// If no host in target, return the domain with https
		return "https://" + domain
	}

	// Check if target host is within the specified domain
	if isWithinDomain(targetHost, domain) {
		// Reconstruct URL with https scheme
		targetURL.Scheme = "https"
		return targetURL.String()
	}

	// If not within domain, return the domain with https
	return "https://" + domain
}

// Helper function to check if a host is within a domain
func isWithinDomain(host, domain string) bool {
	// Direct match
	if host == domain {
		return true
	}

	// Check if host ends with "." + domain
	if strings.HasSuffix(host, "."+domain) {
		// Ensure it's not just a partial match (e.g., "example.com" should not match "notexample.com")
		// by checking the character before the suffix
		suffixIndex := len(host) - len(domain) - 1
		if suffixIndex >= 0 && host[suffixIndex] == '.' {
			return true
		}
	}

	return false
}