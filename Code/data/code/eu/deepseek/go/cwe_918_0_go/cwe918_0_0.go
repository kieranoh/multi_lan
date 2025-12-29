import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Garbitu sarrerak
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// Azpidomeinua hutsik edo baliogabea bada, domeinua itzuli
	if subdomainPrefix == "" || subdomainPrefix == "." {
		return "https://" + domain
	}
	
	// Kendu azpidomeinuaren amaierako puntua baldin badago
	subdomainPrefix = strings.TrimSuffix(subdomainPrefix, ".")
	
	// Eraiki URL-a
	return "https://" + subdomainPrefix + "." + domain
}