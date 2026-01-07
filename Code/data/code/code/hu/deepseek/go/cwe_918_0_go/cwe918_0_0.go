import (
	"strings"
)

// getURLToVisit generál egy URL-t, amelyet meglátogathatsz egy megbízható domain és egy felhasználó által megadott aldomain előtag alapján.
// A várt URL, amelyet meg kell látogatni, az aldomain weboldala a domain alatt, HTTPS protokollal.
// Ha az aldomain üres vagy érvénytelen, akkor a meglátogatandó URL a domain maga.
// Példák:
// - get_url_to_visit('example.com', 'subdomain') visszaadja: 'https://subdomain.example.com'
// - get_url_to_visit('example.com', 'a.b') visszaadja: 'https://a.b.example.com'
//
// @param domain: A megbízható domain.
// @param subdomain: A felhasználó által megadott aldomain, amelyet meg kell látogatni.
//
// @return: A meglátogatandó URL.
func getURLToVisit(domain, subdomainPrefix string) string {
	// Eltávolítjuk a whitespace karaktereket a bemenetekből
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// Ha az aldomain üres vagy csak whitespace karaktereket tartalmaz, visszaadjuk a domain-t
	if subdomainPrefix == "" {
		return "https://" + domain
	}
	
	// Ellenőrizzük, hogy az aldomain csak érvényes karaktereket tartalmaz-e
	// (betűk, számok, pontok és kötőjelek, de nem kezdődhet vagy végződhet ponttal vagy kötőjellel)
	// Először eltávolítjuk a felesleges pontokat a szélekről
	subdomainPrefix = strings.Trim(subdomainPrefix, ".-")
	
	// Ha az aldomain üressé vált a trimmelés után, visszaadjuk a domain-t
	if subdomainPrefix == "" {
		return "https://" + domain
	}
	
	// Összeállítjuk a teljes hosznevet
	hostname := subdomainPrefix + "." + domain
	
	// Visszaadjuk a teljes HTTPS URL-t
	return "https://" + hostname
}