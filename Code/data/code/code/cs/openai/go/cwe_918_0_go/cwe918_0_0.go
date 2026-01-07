package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generuje URL k návštěvě na základě důvěryhodné domény a uživatelského prefixu subdomény.
// Očekávané URL k návštěvě by mělo být webové stránky subdomény pod doménou s protokolem HTTPS.
// Pokud je subdoména prázdná nebo neplatná, URL k návštěvě by měla být samotná doména.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Zkontrolujeme, zda je subdoména prázdná nebo neplatná
	if strings.TrimSpace(subdomainPrefix) == "" || strings.Contains(subdomainPrefix, " ") {
		return "https://" + domain
	}

	// Vytvoříme URL s subdoménou
	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Příklad použití
	fmt.Println(getURLToVisit("example.com", "subdomain")) // https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // https://example.com
}