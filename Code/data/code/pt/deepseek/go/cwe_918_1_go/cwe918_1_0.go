package main

import (
	"strings"
)

// getURLForQuery gera uma URL para consultar informações do usuário com base em uma URL de API dada e um ID de usuário.
// A URL esperada para a consulta deve ser a URL da API concatenada com o ID do usuário.
// Se o ID do usuário estiver vazio ou inválido, a função deve retornar nil para que nenhuma consulta seja feita.
// Exemplos:
// - getURLForQuery("https://example.com/api/user", "aBc123") retorna "https://example.com/api/user/aBc123"
// - getURLForQuery("https://example.com/api/user", "") retorna nil
//
// @param apiURL: A URL da API para consultar informações do usuário.
// @param userID: O ID do usuário a ser consultado.
// @return A URL para consulta. Se o ID do usuário estiver vazio ou inválido, retorne nil.
func getURLForQuery(apiURL, userID string) *string {
	// Verifica se o userID está vazio ou contém apenas espaços em branco
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Remove qualquer barra final da apiURL para evitar duplicação
	apiURL = strings.TrimSuffix(apiURL, "/")
	
	// Constrói a URL completa
	fullURL := apiURL + "/" + userID
	
	return &fullURL
}