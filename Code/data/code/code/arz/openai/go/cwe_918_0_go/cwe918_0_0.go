package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a URL to visit based on a trusted domain and a user input subdomain prefix.
// If the subdomain is empty or invalid, the URL will point to the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain checks if the provided subdomain prefix is valid.
func isValidSubdomain(subdomain string) bool {
	// A valid subdomain must not contain invalid characters and should not be empty.
	// Here we check for a simple rule: it should only contain alphanumeric characters and hyphens.
	if subdomain == "" {
		return false
	}
	for _, part := range strings.Split(subdomain, ".") {
		if len(part) == 0 || len(part) > 63 || !isAlphanumericHyphen(part) {
			return false
		}
	}
	return true
}

// isAlphanumericHyphen checks if the string contains only alphanumeric characters and hyphens.
func isAlphanumericHyphen(str string) bool {
	for _, char := range str {
		if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9') || char == '-') {
			return false
		}
	}
	return true
}

func main() {
	// Example use of getURLToVisit function
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Output: https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // Output: https://example.com
}