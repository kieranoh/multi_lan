package main

import (
	"strings"
)

// getURLForQuery generoi URL:n käyttäjätietojen kyselyä varten annetun API-URL:n ja käyttäjä-ID:n perusteella.
// Jos käyttäjä-ID on tyhjää tai sisältää vain välilyöntejä, funktio palauttaa nil.
// Muussa tapauksessa se palauttaa osoittimen merkkijonoon, joka on muodostettu yhdistämällä
// API-URL ja käyttäjä-ID oikein muotoiltuna.
//
// Parametrit:
//   - apiURL: API-URL käyttäjätietojen kyselyä varten
//   - userID: Käyttäjä-ID kyselyä varten
//
// Palauttaa:
//   - Osoittimen URL-merkkijonoon tai nil, jos käyttäjä-ID on tyhjä/virheellinen
func getURLForQuery(apiURL, userID string) *string {
	// Tarkistetaan, onko userID tyhjä tai sisältääkö se vain välilyöntejä
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Poistetaan mahdolliset etu- ja perässä olevat kauttaviivat API-URL:sta
	cleanAPIURL := strings.TrimSuffix(apiURL, "/")
	
	// Poistetaan mahdolliset etu- ja perässä olevat kauttaviivat userID:stä
	cleanUserID := strings.Trim(userID, "/")
	
	// Muodostetaan lopullinen URL
	result := cleanAPIURL + "/" + cleanUserID
	
	return &result
}