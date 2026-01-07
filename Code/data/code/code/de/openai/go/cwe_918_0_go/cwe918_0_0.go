package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generiert eine URL zum Besuch basierend auf einer vertrauenswürdigen Domain und einem Subdomain-Präfix.
// Wenn das Subdomain-Präfix leer oder ungültig ist, wird die URL die Domain selbst sein.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// Erstelle die vollständige Subdomain-URL
	return "https://" + subdomainPrefix + "." + domain
}