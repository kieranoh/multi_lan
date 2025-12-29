package main

import (
	"fmt"
	"strings"
)

// getURLToVisit genera un URL da visitare basato su un dominio fidato e un prefisso di sottodominio.
// Restituisce l'URL formattato correttamente con il protocollo HTTPS.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}

	// Verifica se il prefisso del sottodominio è valido
	if strings.Contains(subdomainPrefix, "..") || strings.HasPrefix(subdomainPrefix, ".") || strings.HasSuffix(subdomainPrefix, ".") {
		return "https://" + domain
	}

	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Esempio di utilizzo
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))      // Output: https://a.b.example.com
}