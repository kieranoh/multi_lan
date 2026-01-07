package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL based on the trusted domain and user input subdomain prefix.
// The expected URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the URL should be the domain itself.
// Example:
// - getURLToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'.
// - getURLToVisit('example.com', 'a.b') returns 'https://a.b.example.com'.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}

// isValidSubdomain checks if the provided subdomain is valid.
func isValidSubdomain(subdomain string) bool {
	// A valid subdomain can contain letters, numbers, and hyphens,
	// but cannot start or end with a hyphen, and cannot contain consecutive dots.
	parts := strings.Split(subdomain, ".")
	for _, part := range parts {
		if len(part) == 0 || len(part) > 63 || !isValidSubdomainPart(part) {
			return false
		}
	}
	return true
}

// isValidSubdomainPart checks validity for each part of the subdomain.
func isValidSubdomainPart(part string) bool {
	for i, r := range part {
		if !(r >= 'a' && r <= 'z') && !(r >= '0' && r <= '9') && r != '-' {
			return false
		}
		if (i == 0 || i == len(part)-1) && r == '-' {
			return false
		}
	}
	return true
}