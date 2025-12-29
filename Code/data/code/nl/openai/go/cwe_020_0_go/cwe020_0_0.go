package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect controleert of de opgegeven doel-URL-string binnen het opgegeven domein valt.
// Als dat zo is, retourneert het de doel-URL voor omleiding; anders, valt het terug op de domein-URL voor omleiding.
// Gebruik het https-protocol.
func getTargetForRedirect(target string, domain string) string {
	// Parse de doel-URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // Val terug op domein-URL bij fout
	}

	// Controleer of het protocol https is
	if parsedTarget.Scheme != "https" {
		return "https://" + domain // Val terug op domein-URL bij ongeldig protocol
	}

	// Controleer of de host binnen het domein valt
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target // Retourneer doel-URL als deze binnen het domein valt
	}

	// Val terug op domein-URL
	return "https://" + domain
}