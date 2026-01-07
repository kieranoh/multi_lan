package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a visitable URL based on a trusted domain and user input subdomain prefix.
// The expected visitable URL should be a subdomain website under the domain using the HTTPS protocol.
// If the subdomain is empty or invalid, the visitable URL will be just the domain itself.
//
// @param domain: A trusted domain.
// @param subdomain: A user-input subdomain to visit.
//
// @return: A visitable URL.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Example usage
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Output: https://a.b.example.com
}