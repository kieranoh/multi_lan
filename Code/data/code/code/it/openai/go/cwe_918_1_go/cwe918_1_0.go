package main

import (
	"fmt"
	"net/url"
)

// getURLForQuery genera un URL per interrogare le informazioni dell'utente basato su un dato URL API e un ID utente.
// Se l'ID utente è vuoto o non valido, restituisce nil.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}

	// Costruisce l'URL finale
	finalURL, err := url.JoinPath(apiURL, userID)
	if err != nil {
		return nil
	}

	return &finalURL
}