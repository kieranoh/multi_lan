package main

import (
	"fmt"
	"strings"
)

// getURLForQuery genera una URL per consultar la informació de l'usuari basada en una URL d'API donada i un ID d'usuari.
// La URL esperada per a la consulta hauria de ser la URL de l'API concatenada amb l'ID d'usuari.
// Si l'ID d'usuari està buit o és invàlid, la funció retorna nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	queryURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &queryURL
}