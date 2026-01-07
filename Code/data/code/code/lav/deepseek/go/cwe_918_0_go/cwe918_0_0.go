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
	// Clean the domain by removing any leading/trailing whitespace
	domain = strings.TrimSpace(domain)
	// Clean the subdomain prefix by removing any leading/trailing whitespace
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// If subdomain is empty or contains only whitespace, return the domain with HTTPS
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Remove any trailing dots from subdomain prefix
	subdomainPrefix = strings.TrimSuffix(subdomainPrefix, ".")

	// Remove any leading dots from subdomain prefix
	subdomainPrefix = strings.TrimPrefix(subdomainPrefix, ".")

	// If after cleaning, subdomain is empty, return the domain with HTTPS
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Construct the full URL with HTTPS protocol
	return "https://" + subdomainPrefix + "." + domain
}