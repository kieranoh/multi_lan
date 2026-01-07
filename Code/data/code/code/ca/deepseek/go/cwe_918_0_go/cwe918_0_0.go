package main

import (
	"strings"
	"unicode"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Netejar els espais en blanc al principi i al final
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Si el subdomini està buit o és invàlid, retornar només el domini
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// Construir la URL completa
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix comprova si el prefix del subdomini és vàlid
func isValidSubdomainPrefix(prefix string) bool {
	if prefix == "" {
		return false
	}

	// Comprovar que només conté caràcters vàlids per a un subdomini
	for i, ch := range prefix {
		// Els caràcters vàlids són: lletres, dígits, guions i punts
		if !unicode.IsLetter(ch) && !unicode.IsDigit(ch) && ch != '-' && ch != '.' {
			return false
		}

		// El guió no pot estar al principi ni al final d'una etiqueta
		if ch == '-' && (i == 0 || i == len(prefix)-1) {
			return false
		}

		// El punt no pot estar al principi ni al final de tot el prefix
		if ch == '.' && (i == 0 || i == len(prefix)-1) {
			return false
		}

		// No es permeten dos punts consecutius
		if ch == '.' && i > 0 && prefix[i-1] == '.' {
			return false
		}
	}

	// Comprovar que cada etiqueta entre punts té una longitud vàlida
	labels := strings.Split(prefix, ".")
	for _, label := range labels {
		if len(label) == 0 || len(label) > 63 {
			return false
		}
	}

	return true
}