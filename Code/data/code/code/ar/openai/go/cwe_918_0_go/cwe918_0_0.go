package main

import (
	"fmt"
	"strings"
)

// getURLToVisit creates a visitable URL based on a trusted domain and a user-input subdomain prefix.
// It returns the URL as 'https://subdomain.example.com' or just 'https://example.com' if the subdomain is invalid.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Check if the subdomainPrefix is empty or contains invalid characters
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain checks if the provided subdomain prefix is valid.
func isValidSubdomain(subdomain string) bool {
	// A simple check for valid characters (letters, digits, hyphens)
	for _, char := range subdomain {
		if !isAllowedSubdomainChar(char) {
			return false
		}
	}
	return true
}

// isAllowedSubdomainChar determines if a character is allowed in a subdomain.
func isAllowedSubdomainChar(char rune) bool {
	return strings.ContainsRune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.", char)
}

func main() {
	// Example usage
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Output: https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // Output: https://example.com
	fmt.Println(getURLToVisit("example.com", "invalid#char")) // Output: https://example.com
}