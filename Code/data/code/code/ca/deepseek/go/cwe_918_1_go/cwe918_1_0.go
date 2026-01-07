package main

import (
	"strings"
)

// getURLForQuery genera una URL per consultar la informació de l'usuari basada en una URL d'API donada i un ID d'usuari.
// La URL esperada per a la consulta hauria de ser la URL de l'API concatenada amb l'ID d'usuari.
// Si l'ID d'usuari està buit o és invàlid, la funció hauria de retornar nil perquè no es realitzi cap consulta.
// Exemples:
// - getURLForQuery("https://example.com/api/user", "aBc123") retorna 'https://example.com/api/user/aBc123'
// - getURLForQuery("https://example.com/api/user", "") retorna nil
//
// @param apiURL: La URL de l'API per consultar la informació de l'usuari.
// @param userID: L'ID d'usuari per consultar.
// @return La URL per a la consulta. Si l'ID d'usuari està buit o és invàlid, retorna nil.
func getURLForQuery(apiURL, userID string) *string {
	// Comprovar si l'ID d'usuari està buit o és invàlid
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Assegurar-se que la URL de l'API no tingui una barra final
	apiURL = strings.TrimSuffix(apiURL, "/")

	// Construir la URL completa
	fullURL := apiURL + "/" + userID

	// Retornar un punter a la URL
	return &fullURL
}