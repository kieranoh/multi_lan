import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Očistíme vstupy od bílých znaků
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// Pokud je subdoména prázdná nebo neplatná, vrátíme samotnou doménu
	if subdomainPrefix == "" || subdomainPrefix == "." {
		return "https://" + domain
	}
	
	// Očistíme subdoménu od případných úvodních nebo koncových teček
	subdomainPrefix = strings.Trim(subdomainPrefix, ".")
	
	// Sestavíme URL
	return "https://" + subdomainPrefix + "." + domain
}