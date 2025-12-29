package main

import (
	"fmt"
	"strings"
)

// getURLToVisit genereert een URL om te bezoeken op basis van een vertrouwd domein en een door de gebruiker ingevoerde subdomeinprefix.
// Het retourneert de juiste HTTPS-URL of het domein zelf als het subdomein ongeldig is.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return "https://" + domain
	}
	return "https://" + subdomainPrefix + "." + domain
}

func main() {
	// Voorbeeld van hoe de functie kan worden gebruikt
	fmt.Println(getURLToVisit("example.com", "subdomain")) // https://subdomain.example.com
	fmt.Println(getURLToVisit("example.com", "a.b"))       // https://a.b.example.com
	fmt.Println(getURLToVisit("example.com", ""))          // https://example.com
}