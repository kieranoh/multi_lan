import (
	"strings"
	"regexp"
)

func getURLToVisit(domain, subdomainPrefix string) string {
	// Bereinige die Eingaben von führenden/nachgestellten Leerzeichen
	domain = strings.TrimSpace(domain)
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// Wenn die Subdomain leer oder ungültig ist, gebe die Domain-URL zurück
	if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
		return "https://" + domain
	}
	
	// Entferne mögliche führende Punkte von der Subdomain
	subdomainPrefix = strings.TrimPrefix(subdomainPrefix, ".")
	
	// Baue die vollständige URL
	return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain prüft, ob die Subdomain gültig ist
func isValidSubdomain(subdomain string) bool {
	// Eine gültige Subdomain sollte:
	// 1. Nicht leer sein
	// 2. Nur Buchstaben, Zahlen, Punkte und Bindestriche enthalten
	// 3. Nicht mit oder enden mit einem Punkt oder Bindestrich
	// 4. Nicht länger als 63 Zeichen pro Label sein (vereinfachte Prüfung)
	
	if subdomain == "" {
		return false
	}
	
	// Prüfe auf ungültige Zeichen
	validSubdomainRegex := regexp.MustCompile(`^[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?(\.[a-zA-Z0-9]([a-zA-Z0-9\-]*[a-zA-Z0-9])?)*$`)
	if !validSubdomainRegex.MatchString(subdomain) {
		return false
	}
	
	// Prüfe, dass keine aufeinanderfolgenden Punkte vorhanden sind
	if strings.Contains(subdomain, "..") {
		return false
	}
	
	// Prüfe, dass die Subdomain nicht mit Punkt oder Bindestrich beginnt oder endet
	if strings.HasPrefix(subdomain, "-") || strings.HasSuffix(subdomain, "-") ||
		strings.HasPrefix(subdomain, ".") || strings.HasSuffix(subdomain, ".") {
		return false
	}
	
	// Prüfe die Länge jedes Labels (zwischen den Punkten)
	labels := strings.Split(subdomain, ".")
	for _, label := range labels {
		if len(label) > 63 {
			return false
		}
		if len(label) == 0 {
			return false
		}
	}
	
	return true
}