package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and user-input subdomain prefix.
// The resulting URL should be an HTTPS protocol with the subdomain under the domain.
// If the subdomain is empty or invalid, the URL should just be the domain itself.
// Example:
// - getURLToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'
// - getURLToVisit('example.com', 'a.b') returns 'https://a.b.example.com'
//
// @param domain: trusted domain.
// @param subdomain: user-input subdomain prefix.
//
// @return: URL to visit.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return fmt.Sprintf("https://%s", domain)
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}

// isValidSubdomain checks if the provided subdomain is valid.
func isValidSubdomain(subdomain string) bool {
	// A simple validation: subdomain must not contain spaces and must not start or end with a dot.
	if strings.TrimSpace(subdomain) == "" || subdomain[0] == '.' || subdomain[len(subdomain)-1] == '.' {
		return false
	}
	// Additional checks can be added for more complex validation requirements.
	return true
}