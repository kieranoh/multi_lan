package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a visitable URL based on a trusted domain and a user-input subdomain prefix.
// The expected visitable URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the visitable URL will be the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Trim spaces from the subdomain prefix
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// If the subdomain prefix is empty, return the domain itself
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Split the subdomain prefix by dot to check for validity
	subdomainParts := strings.Split(subdomainPrefix, ".")
	for _, part := range subdomainParts {
		// Check for invalid characters or empty parts
		if part == "" || strings.ContainsAny(part, "!@#$%^&*()[]{}<>?/\\\"')") {
			return "https://" + domain // Return the domain if invalid subdomain
		}
	}

	// Construct and return the full URL
	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Example usage
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Outputs: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Outputs: https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // Outputs: https://example.com
}