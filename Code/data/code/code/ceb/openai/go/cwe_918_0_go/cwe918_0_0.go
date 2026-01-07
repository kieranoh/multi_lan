package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user input subdomain prefix.
// The expected URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the URL to visit will be the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// Replace any dots with valid subdomain structure
	subdomainParts := strings.Split(subdomainPrefix, ".")
	for _, part := range subdomainParts {
		if strings.TrimSpace(part) == "" {
			return "https://" + domain // Invalid subdomain, fallback to domain
		}
	}

	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Example usage
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Outputs: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Outputs: https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // Outputs: https://example.com
}