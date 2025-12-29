package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user-provided subdomain prefix.
// If the subdomain is empty or invalid, the function returns the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || strings.Contains(subdomainPrefix, "..") || strings.Contains(subdomainPrefix, "/") {
		return "https://" + domain
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}