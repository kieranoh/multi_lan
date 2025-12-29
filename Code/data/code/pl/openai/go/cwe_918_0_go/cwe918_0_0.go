package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user-provided subdomain prefix.
// If the subdomain is empty or invalid, it returns the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || strings.Contains(subdomainPrefix, ".") {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Example usage:
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Output: https://example.com
}