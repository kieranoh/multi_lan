package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect vérifie si la chaîne d'URL cible fournie se trouve dans le domaine fourni.
// Si c'est le cas, elle renvoie l'URL cible pour la redirection ; sinon, elle revient à l'URL du domaine pour la redirection.
// Utilise le protocole https.
func getTargetForRedirect(target string, domain string) string {
	// Vérifie si l'URL cible a le protocole https
	if !strings.HasPrefix(target, "https://") {
		return "https://" + domain
	}

	// Parse l'URL cible
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain
	}

	// Vérifie si le domaine de l'URL cible correspond au domaine fourni
	if strings.HasSuffix(parsedURL.Hostname(), domain) {
		return target
	}

	return "https://" + domain
}