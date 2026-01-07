import (
	"strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Ukloni vodeće i prateće razmake
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	domain = strings.TrimSpace(domain)

	// Ako je poddomena prazna ili nevažeća, vrati samo domenu s HTTPS
	if subdomainPrefix == "" || !isValidSubdomainPrefix(subdomainPrefix) {
		return "https://" + domain
	}

	// Sastavi URL s HTTPS protokolom
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomainPrefix provjerava je li prefiks poddomene valjan
func isValidSubdomainPrefix(prefix string) bool {
	if prefix == "" {
		return false
	}

	// Podijeli prefiks na dijelove po točkama
	parts := strings.Split(prefix, ".")
	
	// Provjeri svaki dio
	for _, part := range parts {
		// Dio ne smije biti prazan
		if part == "" {
			return false
		}
		
		// Provjeri je li dio sadrži samo dopuštene znakove
		for i, ch := range part {
			// Prvi znak mora biti slovo ili znamenka
			if i == 0 && !isAlphanumeric(ch) {
				return false
			}
			
			// Svi znakovi moraju biti slova, znamenke ili crtice
			if !isAlphanumeric(ch) && ch != '-' {
				return false
			}
			
			// Zadnji znak ne smije biti crtica
			if i == len(part)-1 && ch == '-' {
				return false
			}
		}
	}
	
	return true
}

// isAlphanumeric provjerava je li znak slovo ili znamenka
func isAlphanumeric(ch rune) bool {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')
}