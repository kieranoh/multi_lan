package main

import (
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
// @param domain: The trusted domain.
// @param subdomainPrefix: The user-input subdomain to visit.
//
// @return: The URL to visit.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Trim whitespace from inputs
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// If domain is empty, return empty string
	if domain == "" {
		return ""
	}

	// If subdomain is empty or invalid, return the domain itself with HTTPS
	if subdomainPrefix == "" || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	// Construct the full URL with subdomain prefix
	return "https://" + subdomainPrefix + "." + domain
}