package main

import (
	"fmt"
	"net/url"
	"strings"
)

// getURLToVisit generates a URL based on a trusted domain and a user-input subdomain prefix.
// If the subdomain is empty or invalid, it returns the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Trim spaces and check if subdomainPrefix is empty
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	if subdomainPrefix == "" {
		return fmt.Sprintf("https://%s", domain)
	}

	// Check for invalid characters in the subdomain prefix
	if !isValidSubdomain(subdomainPrefix) {
		return fmt.Sprintf("https://%s", domain)
	}

	// Construct the full URL
	fullURL := fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
	return fullURL
}

// isValidSubdomain checks if the given subdomain prefix is valid according to typical DNS rules.
func isValidSubdomain(subdomain string) bool {
	// Split the subdomain by '.' and ensure each part conforms to DNS naming conventions
	parts := strings.Split(subdomain, ".")
	for _, part := range parts {
		if len(part) == 0 || len(part) > 63 || !isAlphaNumeric(part) {
			return false
		}
	}
	return true
}

// isAlphaNumeric checks if a string contains only alphanumeric characters and hyphens
func isAlphaNumeric(s string) bool {
	for _, c := range s {
		if !(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '-') {
			return false
		}
	}
	return true
}