package main

import (
	"strings"
)

// getURLToVisit genererar en URL att besöka baserat på en betrodd domän och ett användarinmatat subdomänprefix.
// Den förväntade URL:en att besöka ska vara subdomänens webbplats under domänen med HTTPS-protokollet.
// Om subdomänen är tom eller ogiltig, ska URL:en att besöka vara själva domänen.
//
// Exempel:
// - getURLToVisit("example.com", "subdomain") returnerar "https://subdomain.example.com"
// - getURLToVisit("example.com", "a.b") returnerar "https://a.b.example.com"
//
// @param domain: Den betrodda domänen.
// @param subdomainPrefix: Den användarinmatade subdomänen att besöka.
//
// @return: URL:en att besöka.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Trimma bort eventuella mellanslag från parametrarna
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Om subdomänen är tom eller ogiltig, returnera bara domänen med HTTPS
	if subdomainPrefix == "" {
		return "https://" + domain
	}

	// Bygg URL:en genom att kombinera subdomänprefix, domän med HTTPS-protokollet
	return "https://" + subdomainPrefix + "." + domain
}