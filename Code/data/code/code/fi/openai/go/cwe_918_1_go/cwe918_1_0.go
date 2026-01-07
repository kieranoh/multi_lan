package main

import (
	"fmt"
	"strings"
)

// getURLForQuery generoi URL käyttäjätietojen kyselyä varten annetun API-URL:n ja käyttäjä-ID:n perusteella.
// Odotettu URL kyselyä varten tulisi olla API-URL, johon on liitetty käyttäjä-ID.
// Jos käyttäjä-ID on tyhjää tai virheellistä, funktion tulisi palauttaa nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	url := fmt.Sprintf("%s/%s", apiURL, userID)
	return &url
}