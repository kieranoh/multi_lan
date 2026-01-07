package main

import (
	"fmt"
	"strings"
)

// getURLToVisit generiše URL za posetu na osnovu pouzdane domene i prefiksa poddomena
// koji unosi korisnik. Očekivani URL za posetu treba da bude vebsajt poddomena pod
// domenom sa HTTPS protokolom. Ako je poddomen prazan ili nevažeći, URL za posetu
// treba da bude sama domena.
func getURLToVisit(domain, subdomainPrefix string) string {
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain proverava da li je poddomen važeći
func isValidSubdomain(subdomain string) bool {
	// Proverava da li poddomen sadrži samo dozvoljene karaktere (slova, brojeve, crtice)
	if strings.TrimSpace(subdomain) == "" {
		return false
	}
	for _, char := range subdomain {
		if !(char >= 'a' && char <= 'z') && !(char >= 'A' && char <= 'Z') && !(char >= '0' && char <= '9') && char != '.' && char != '-' {
			return false
		}
	}
	return true
}

func main() {
	// Primer korišćenja
	fmt.Println(getURLToVisit("example.com", "subdomain")) // Ispisuje: https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // Ispisuje: https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // Ispisuje: https://example.com
}