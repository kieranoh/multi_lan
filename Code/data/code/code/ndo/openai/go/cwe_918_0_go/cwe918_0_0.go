package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a visitable URL based on a trusted domain and a user-provided subdomain prefix.
// The visitable URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the visitable URL should be the domain itself.
// 
// Example:
// - getURLToVisit("example.com", "subdomain") returns "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") returns "https://a.b.example.com"
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}