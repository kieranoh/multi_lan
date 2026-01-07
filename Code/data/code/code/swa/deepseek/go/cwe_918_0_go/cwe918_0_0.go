package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and user-input subdomain prefix.
// The expected URL to visit should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the URL to visit should be the domain itself.
//
// Examples:
// - getURLToVisit("example.com", "subdomain") returns "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") returns "https://a.b.example.com"
//
// @param domain: Trusted domain.
// @param subdomainPrefix: User-input subdomain to visit.
//
// @return: URL to visit.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Clean the inputs by trimming whitespace
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// If subdomain is empty or invalid, return the domain with HTTPS
	if subdomainPrefix == "" || subdomainPrefix == "." {
		return fmt.Sprintf("https://%s", domain)
	}

	// Remove leading or trailing dots from subdomain prefix
	subdomainPrefix = strings.Trim(subdomainPrefix, ".")

	// If after trimming it becomes empty, return the domain
	if subdomainPrefix == "" {
		return fmt.Sprintf("https://%s", domain)
	}

	// Construct the full URL with HTTPS protocol
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}