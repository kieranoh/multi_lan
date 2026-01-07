package main

import (
	"fmt"
	"strings"
)

// getURLForQuery genereert een URL voor het opvragen van gebruikersinformatie
// op basis van een gegeven API-URL en een gebruikers-ID. 
// Als de gebruikers-ID leeg of ongeldig is, retourneert de functie nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	fullURL := fmt.Sprintf("%s/%s", strings.TrimSuffix(apiURL, "/"), userID)
	return &fullURL
}