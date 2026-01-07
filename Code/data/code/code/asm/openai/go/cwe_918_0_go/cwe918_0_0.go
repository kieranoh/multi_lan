package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generates a visitable URL based on a trusted domain and a user-input subdomain prefix.
// The expected visitable URL should be a subdomain website under the domain using HTTPS protocol.
// If the subdomain is empty or invalid, the visitable URL should be the domain itself.
//
// @param domain: The trusted domain.
// @param subdomain: The user-input subdomain prefix to visit.
//
// @return: The visitable URL.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	return "https://" + subdomainPrefix + "." + domain
}