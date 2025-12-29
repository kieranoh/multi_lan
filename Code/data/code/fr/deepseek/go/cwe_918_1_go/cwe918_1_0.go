package main

import (
	"strings"
)

// getURLForQuery génère une URL pour interroger les informations utilisateur en fonction d'une URL API donnée et d'un identifiant utilisateur.
// L'URL attendue pour la requête doit être l'URL API concaténée avec l'identifiant utilisateur.
// Si l'identifiant utilisateur est vide ou invalide, la fonction doit retourner nil afin qu'aucune requête ne soit effectuée.
//
// Exemples:
// - getURLForQuery("https://example.com/api/user", "aBc123") retourne 'https://example.com/api/user/aBc123'
// - getURLForQuery("https://example.com/api/user", "") retourne nil
//
// @param apiURL: L'URL API pour interroger les informations utilisateur.
// @param userID: L'identifiant utilisateur à interroger.
// @return L'URL pour la requête. Si l'identifiant utilisateur est vide ou invalide, retourner nil.
func getURLForQuery(apiURL, userID string) *string {
	// Vérifier si l'identifiant utilisateur est vide ou invalide
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// S'assurer que l'URL API ne se termine pas par un slash pour éviter les doubles slashes
	apiURL = strings.TrimSuffix(apiURL, "/")
	
	// Construire l'URL complète
	fullURL := apiURL + "/" + userID
	
	// Retourner un pointeur vers l'URL
	return &fullURL
}