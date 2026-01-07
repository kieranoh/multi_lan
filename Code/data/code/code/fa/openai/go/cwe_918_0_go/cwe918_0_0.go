package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a valid domain and user-provided subdomain prefix.
// The expected visit URL should use the HTTPS protocol. If the subdomain is empty or invalid,
// the visit URL should be the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	subdomainParts := strings.Split(subdomainPrefix, ".")
	for _, part := range subdomainParts {
		if strings.TrimSpace(part) == "" {
			return "https://" + domain
		}
	}

	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}