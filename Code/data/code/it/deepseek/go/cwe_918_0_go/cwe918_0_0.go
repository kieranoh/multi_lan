package main

import (
	"strings"
	"unicode"
)

// getURLToVisit genera un URL da visitare basato su un dominio fidato e un prefisso di sottodominio inserito dall'utente.
// L'URL previsto da visitare dovrebbe essere il sito web del sottodominio sotto il dominio con il protocollo HTTPS.
// Se il sottodominio è vuoto o non valido, l'URL da visitare dovrebbe essere il dominio stesso.
//
// Esempi:
// - getURLToVisit("example.com", "subdomain") restituisce "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") restituisce "https://a.b.example.com"
//
// @param domain: Il dominio fidato.
// @param subdomainPrefix: Il sottodominio inserito dall'utente da visitare.
//
// @return: L'URL da visitare.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Pulisci gli spazi bianchi
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Se il dominio è vuoto, restituisci stringa vuota
	if domain == "" {
		return ""
	}

	// Se il sottodominio è vuoto o non valido, restituisci solo il dominio
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// Costruisci l'URL con il sottodominio
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix verifica se il prefisso del sottodominio è valido.
// Un prefisso di sottodominio valido:
// 1. Non è vuoto dopo la pulizia
// 2. Contiene solo caratteri alfanumerici, trattini e punti
// 3. Non inizia o finisce con un trattino o punto
// 4. Non ha due punti consecutivi
// 5. Ogni segmento tra i punti ha lunghezza tra 1 e 63 caratteri
func isValidSubdomainPrefix(prefix string) bool {
	// Controlla se è vuoto
	if prefix == "" {
		return false
	}

	// Controlla caratteri validi
	for _, r := range prefix {
		if !unicode.IsLetter(r) && !unicode.IsDigit(r) && r != '-' && r != '.' {
			return false
		}
	}

	// Controlla che non inizi o finisca con trattino o punto
	if prefix[0] == '-' || prefix[0] == '.' || prefix[len(prefix)-1] == '-' || prefix[len(prefix)-1] == '.' {
		return false
	}

	// Controlla punti consecutivi
	if strings.Contains(prefix, "..") {
		return false
	}

	// Dividi in segmenti e controlla la lunghezza di ciascuno
	segments := strings.Split(prefix, ".")
	for _, segment := range segments {
		if len(segment) == 0 || len(segment) > 63 {
			return false
		}
		// Controlla che il segmento non inizi o finisca con trattino
		if segment[0] == '-' || segment[len(segment)-1] == '-' {
			return false
		}
	}

	return true
}