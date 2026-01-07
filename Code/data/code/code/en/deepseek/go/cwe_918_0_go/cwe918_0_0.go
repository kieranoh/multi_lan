package main

import (
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user-input subdomain prefix.
// The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol.
// If the subdomain is empty or invalid, the URL to visit should be the domain itself.
// Examples:
// - getURLToVisit("example.com", "subdomain") returns "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") returns "https://a.b.example.com"
//
// @param domain: The trusted domain.
// @param subdomainPrefix: The user-input subdomain to visit.
// @return: The URL to visit.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Trim whitespace from inputs
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// If subdomain is empty or invalid (only whitespace), return domain with HTTPS
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Construct the full subdomain by appending the domain
	fullSubdomain := subdomainPrefix + "." + domain

	// Return the HTTPS URL
	return "https://" + fullSubdomain
}