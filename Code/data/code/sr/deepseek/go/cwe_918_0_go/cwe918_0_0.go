import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Ukloni vodeće i prateće beline
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)

	// Proveri da li je poddomen prazan ili nevažeći
	if subdomainPrefix == "" || strings.ContainsAny(subdomainPrefix, " /\\?#") {
		return "https://" + domain
	}

	// Proveri da li poddomen već sadrži tačke i obradi ih
	subdomainParts := strings.Split(subdomainPrefix, ".")
	var validParts []string
	for _, part := range subdomainParts {
		part = strings.TrimSpace(part)
		if part != "" {
			validParts = append(validParts, part)
		}
	}

	// Ako nema validnih delova, vrati samo domenu
	if len(validParts) == 0 {
		return "https://" + domain
	}

	// Kreiraj URL
	subdomain := strings.Join(validParts, ".")
	return "https://" + subdomain + "." + domain
}