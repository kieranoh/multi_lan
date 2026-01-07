package main

import (
	"fmt"
	"strings"
)

// getURLToVisit génère une URL à visiter basée sur un domaine de confiance et un préfixe de sous-domaine saisi par l'utilisateur.
// Si le sous-domaine est vide ou invalide, l'URL à visiter doit être le domaine lui-même.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || strings.Contains(subdomainPrefix, "..") || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	normalizedSubdomain := strings.TrimSpace(subdomainPrefix)
	return "https://" + normalizedSubdomain + "." + domain
}