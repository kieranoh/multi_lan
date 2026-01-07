package main

import (
	"strings"
)

// getURLForQuery génère une URL pour interroger les informations utilisateur
// en fonction d'une URL API donnée et d'un identifiant utilisateur.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	fullURL := apiURL + "/" + userID
	return &fullURL
}