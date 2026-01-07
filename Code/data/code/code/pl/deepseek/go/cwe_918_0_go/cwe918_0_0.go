package main

import (
	"net/url"
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Usuń białe znaki z początku i końca
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Jeśli subdomena jest pusta lub nieprawidłowa, zwróć samą domenę
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// Zbuduj pełną subdomenę
	fullSubdomain := subdomainPrefix + "." + domain

	// Utwórz URL z protokołem HTTPS
	return "https://" + fullSubdomain
}

// isValidSubdomainPrefix sprawdza, czy prefiks subdomeny jest prawidłowy
func isValidSubdomainPrefix(subdomainPrefix string) bool {
	// Sprawdź, czy prefiks nie jest pusty po przycięciu białych znaków
	if strings.TrimSpace(subdomainPrefix) == "" {
		return false
	}

	// Sprawdź, czy prefiks zawiera tylko dozwolone znaki dla subdomen
	// Zgodnie z RFC 1035: litery, cyfry i myślniki, nie może zaczynać się ani kończyć myślnikiem
	parts := strings.Split(subdomainPrefix, ".")
	for _, part := range parts {
		if len(part) == 0 {
			return false
		}

		// Sprawdź każdy znak w części
		for i, r := range part {
			// Dozwolone znaki: litery, cyfry, myślnik
			if !((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z') || (r >= '0' && r <= '9') || r == '-') {
				return false
			}

			// Myślnik nie może być na początku ani na końcu
			if (i == 0 || i == len(part)-1) && r == '-' {
				return false
			}
		}
	}

	return true
}