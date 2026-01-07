package main

import (
	"fmt"
	"strings"
)

// getURLToVisit genererar en URL att besöka baserat på en betrodd domän och ett användarinmatat subdomänprefix.
// Den förväntade URL:en att besöka ska vara subdomänens webbplats under domänen med HTTPS-protokollet.
// Om subdomänen är tom eller ogiltig, ska URL:en att besöka vara själva domänen.
func getURLToVisit(domain, subdomainPrefix string) string {
	if strings.TrimSpace(subdomainPrefix) == "" {
		return fmt.Sprintf("https://%s", domain)
	}
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}