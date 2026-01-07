package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect controlla se la stringa dell'URL di destinazione fornita è all'interno del dominio fornito.
// Se sì, restituisce l'URL di destinazione per il reindirizzamento; altrimenti, torna all'URL del dominio per il reindirizzamento.
// Usa il protocollo https.
func getTargetForRedirect(target string, domain string) string {
	// Parse the target URL
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Check if the target's host contains the domain
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	// Return the domain URL with HTTPS
	return "https://" + domain
}