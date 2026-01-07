package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect checks if the given URL address is under the provided domain.
// If it is, it returns the URL address for redirection; otherwise, it returns the domain's URL for redirection.
// It uses the https protocol.
func getTargetForRedirect(target string, domain string) string {
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the target's hostname contains the domain
	if strings.Contains(parsedTarget.Hostname(), domain) {
		return target
	}
	return "https://" + domain
}