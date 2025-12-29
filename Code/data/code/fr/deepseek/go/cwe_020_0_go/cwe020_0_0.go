package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect vérifie si la chaîne d'URL cible fournie se trouve dans le domaine fourni.
// Si c'est le cas, renvoie l'URL cible pour la redirection ; sinon, revient à l'URL du domaine pour la redirection.
// Utilise le protocole https.
func getTargetForRedirect(target string, domain string) string {
	// Parse l'URL cible
	targetURL, err := url.Parse(target)
	if err != nil {
		// En cas d'erreur de parsing, retourne l'URL du domaine avec https
		return "https://" + domain
	}

	// S'assurer que l'URL cible a un schéma (protocole)
	if targetURL.Scheme == "" {
		// Si pas de schéma, ajouter https et re-parser
		targetURL, err = url.Parse("https://" + target)
		if err != nil {
			return "https://" + domain
		}
	}

	// Extraire l'hôte de l'URL cible
	host := targetURL.Hostname()
	if host == "" {
		return "https://" + domain
	}

	// Vérifier si l'hôte se termine par le domaine fourni
	if strings.HasSuffix(host, "."+domain) || host == domain {
		// S'assurer que le schéma est https
		targetURL.Scheme = "https"
		// Reconstruire l'URL avec le schéma https
		return targetURL.String()
	}

	// Si le domaine ne correspond pas, retourner l'URL du domaine avec https
	return "https://" + domain
}