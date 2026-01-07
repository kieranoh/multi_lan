package main

import (
	"fmt"
	"strings"
)

// getURLToVisit genera una URL per visitar basada en un domini de confiança i un prefix de subdomini introduït per l'usuari.
// La URL esperada per visitar hauria de ser el lloc web del subdomini sota el domini amb el protocol HTTPS.
// Si el subdomini està buit o és invàlid, la URL a visitar hauria de ser el domini mateix.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain comprova si el subdomini és vàlid segons les regles generals.
func isValidSubdomain(subdomain string) bool {
	// Es pot afegir més lògica per validar el subdomini segons les regles necessàries
	// en aquest cas, només comprovem que no contingui caràcters no vàlids
	if strings.Contains(subdomain, " ") || strings.Contains(subdomain, "..") {
		return false
	}
	return true
}