package main

import (
	"strings"
	"unicode"
)

// getURLToVisit génère une URL à visiter basée sur un domaine de confiance et un préfixe de sous-domaine.
// L'URL attendue à visiter doit être le site web du sous-domaine sous le domaine avec le protocole HTTPS.
// Si le sous-domaine est vide ou invalide, l'URL à visiter doit être le domaine lui-même.
// Exemples:
// - getURLToVisit("example.com", "subdomain") retourne "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") retourne "https://a.b.example.com"
func getURLToVisit(domain, subdomainPrefix string) string {
	// Nettoyer les espaces
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Vérifier si le domaine est vide
	if domain == "" {
		return ""
	}

	// Vérifier si le sous-domaine est vide ou invalide
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}

	// Construire l'URL avec le sous-domaine
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain vérifie si un sous-domaine est valide selon les règles DNS
func isValidSubdomain(subdomain string) bool {
	if subdomain == "" {
		return false
	}

	// Vérifier la longueur totale (max 253 caractères pour un nom d'hôte complet)
	if len(subdomain) > 253 {
		return false
	}

	// Diviser par points pour vérifier chaque label
	labels := strings.Split(subdomain, ".")
	for _, label := range labels {
		// Vérifier la longueur de chaque label (1-63 caractères)
		if len(label) < 1 || len(label) > 63 {
			return false
		}

		// Vérifier que le label commence et se termine par un caractère alphanumérique
		if len(label) == 0 || !isAlphanumeric(rune(label[0])) || !isAlphanumeric(rune(label[len(label)-1])) {
			return false
		}

		// Vérifier que tous les caractères sont valides
		for _, ch := range label {
			if !isValidSubdomainChar(ch) {
				return false
			}
		}
	}

	return true
}

// isValidSubdomainChar vérifie si un caractère est valide pour un sous-domaine
func isValidSubdomainChar(ch rune) bool {
	// Les caractères valides sont: lettres, chiffres et tiret
	return unicode.IsLetter(ch) || unicode.IsDigit(ch) || ch == '-'
}

// isAlphanumeric vérifie si un caractère est alphanumérique
func isAlphanumeric(ch rune) bool {
	return unicode.IsLetter(ch) || unicode.IsDigit(ch)
}