package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect comprova si la cadena d'URL de destinació proporcionada es troba dins del domini proporcionat.
// Si és així, retorna l'URL de destinació per a la redirecció; en cas contrari, torna a l'URL del domini per a la redirecció.
// Utilitza el protocol https.
func getTargetForRedirect(target string, domain string) string {
	parsedTarget, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // retornem al domini si l'URL no és vàlid
	}

	// Comprovem si el domini del target coincideix amb el domini proporcionat
	if strings.HasSuffix(parsedTarget.Hostname(), domain) {
		return target
	}

	return "https://" + domain
}