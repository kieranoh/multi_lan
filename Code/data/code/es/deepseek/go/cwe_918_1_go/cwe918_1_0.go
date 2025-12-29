package main

import (
	"strings"
)

// getURLForQuery genera una URL para consultar información del usuario basada en una URL de API dada y un ID de usuario.
// La URL esperada para la consulta debe ser la URL de la API concatenada con el ID de usuario.
// Si el ID de usuario está vacío o es inválido, la función devuelve nil para que no se realice ninguna consulta.
//
// Ejemplos:
// - getURLForQuery("https://example.com/api/user", "aBc123") devuelve 'https://example.com/api/user/aBc123'
// - getURLForQuery("https://example.com/api/user", "") devuelve nil
//
// @param apiURL: La URL de la API para consultar información del usuario.
// @param userID: El ID de usuario para consultar.
//
// @return La URL para la consulta. Si el ID de usuario está vacío o es inválido, devuelve nil.
func getURLForQuery(apiURL, userID string) *string {
	// Verificar si el userID está vacío o contiene solo espacios en blanco
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Construir la URL completa
	// Asegurarse de que la apiURL no termine con "/" para evitar dobles barras
	apiURL = strings.TrimSuffix(apiURL, "/")
	result := apiURL + "/" + userID

	return &result
}