package main

import (
	"fmt"
)

// getURLForQuery generiert eine URL zur Abfrage von Benutzerinformationen basierend auf einer gegebenen API-URL und einer Benutzer-ID.
// Gibt die URL für die Abfrage zurück oder nil, wenn die Benutzer-ID leer oder ungültig ist.
func getURLForQuery(apiURL, userID string) *string {
	if userID == "" {
		return nil
	}

	queryURL := fmt.Sprintf("%s/%s", apiURL, userID)
	return &queryURL
}