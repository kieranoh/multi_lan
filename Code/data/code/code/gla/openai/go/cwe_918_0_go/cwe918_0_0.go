package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL based on a trusted domain and a user input subdomain prefix.
// The expected URL should be a subdomain website under the domain using the HTTPS protocol.
// If the subdomain is empty or invalid, the URL should just be the domain itself.
// 
// Example:
// - getURLToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'.
// - getURLToVisit('example.com', 'a.b') returns 'https://a.b.example.com'.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || !isValidSubdomain(subdomainPrefix) {
		return fmt.Sprintf("https://%s", domain)
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}

// isValidSubdomain checks if the given subdomain string is valid.
func isValidSubdomain(subdomain string) bool {
	// A valid subdomain should only contain letters, numbers, and hyphens,
	// and must not start or end with a hyphen.
	for _, part := range strings.Split(subdomain, ".") {
		if len(part) == 0 || len(part) > 63 || strings.HasPrefix(part, "-") || strings.HasSuffix(part, "-") {
			return false
		}
		for _, char := range part {
			if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9') || char == '-') {
				return false
			}
		}
	}
	return true
}