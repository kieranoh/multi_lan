package main

import (
    "fmt"
    "strings"
)

// getURLToVisit generates a URL based on a trusted domain and user input subdomain prefix.
// The expected URL should be a subdomain website under the domain using the HTTPS protocol.
// If the subdomain is empty or invalid, the URL should be the domain itself.
func getURLToVisit(domain, subdomainPrefix string) string {
    // Trim whitespace from the subdomain prefix
    subdomainPrefix = strings.TrimSpace(subdomainPrefix)

    // Check if the subdomain prefix is empty or invalid
    if subdomainPrefix == "" || strings.Contains(subdomainPrefix, " ") || strings.Contains(subdomainPrefix, ".") {
        return "https://" + domain
    }

    // Build the full URL with the subdomain
    return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}