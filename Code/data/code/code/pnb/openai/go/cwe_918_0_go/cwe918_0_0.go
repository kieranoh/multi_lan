package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user-input subdomain prefix.
// The expected visiting URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the visiting URL should be the domain itself.
// 
// Example:
// - getURLToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'.
// - getURLToVisit('example.com', 'a.b') returns 'https://a.b.example.com'.
//
// @param domain: The trusted domain.
// @param subdomain: The user-input subdomain to visit.
//
// @return: The URL to visit.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// Ensure the subdomain is valid (for example, it should not contain illegal characters)
	// Here we just check that it has valid characters (letters, numbers, hyphens, and dots)
	for _, part := range strings.Split(subdomainPrefix, ".") {
		if strings.TrimSpace(part) == "" || !isValidSubdomainPart(part) {
			return "https://" + domain
		}
	}

	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPart checks if a subdomain part is valid.
func isValidSubdomainPart(part string) bool {
	for _, char := range part {
		if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9') || char == '-' || char == '.') {
			return false
		}
	}
	return true
}