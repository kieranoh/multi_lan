package main

import (
	"fmt"
	"net/url"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user input subdomain prefix.
// The expected visit URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the URL should be the domain itself.
// For example:
// - getURLToVisit("example.com", "subdomain") returns "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") returns "https://a.b.example.com"
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain checks if the provided subdomain is valid.
// A valid subdomain must contain only letters, numbers, and hyphens, and must not start or end with a hyphen.
func isValidSubdomain(subdomain string) bool {
	if len(subdomain) == 0 || strings.HasPrefix(subdomain, "-") || strings.HasSuffix(subdomain, "-") {
		return false
	}
	for _, part := range strings.Split(subdomain, ".") {
		if !isAlphanumericOrHyphen(part) || len(part) == 0 {
			return false
		}
	}
	return true
}

// isAlphanumericOrHyphen checks if a string contains only letters, numbers, or hyphens.
func isAlphanumericOrHyphen(s string) bool {
	for _, char := range s {
		if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9') || char == '-') {
			return false
		}
	}
	return true
}