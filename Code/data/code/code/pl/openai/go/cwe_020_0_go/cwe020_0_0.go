package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect sprawdza, czy podany ciąg URL docelowego znajduje się w podanej domenie.
// Jeśli tak, zwraca URL docelowy do przekierowania; w przeciwnym razie, zwraca URL domeny do przekierowania
// używając protokołu https.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the target's host contains the domain
	if strings.Contains(parsedTarget.Host, domain) {
		return target
	}

	// If not, return the domain with https protocol
	return "https://" + domain
}