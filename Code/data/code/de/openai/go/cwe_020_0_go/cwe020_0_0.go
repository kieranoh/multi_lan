package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect überprüft, ob die angegebene Ziel-URL-Zeichenfolge innerhalb der angegebenen Domain liegt.
// Wenn ja, gibt es die Ziel-URL für die Weiterleitung zurück; andernfalls fällt es auf die Domain-URL für die Weiterleitung zurück.
// Es wird das https-Protokoll verwendet.
func getTargetForRedirect(target string, domain string) string {
	// Um sicherzustellen, dass die Domain mit "https://" verwendet wird
	domainURL := "https://" + domain

	// Parsen der Ziel-URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return domainURL // Fehler beim Parsen, zum sicheren Fallback
	}

	// Überprüfen, ob die Ziel-URL zur angegebenen Domain gehört
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	return domainURL
}