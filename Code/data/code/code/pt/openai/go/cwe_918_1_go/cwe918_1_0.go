package main

import (
	"fmt"
	"strings"
)

// getURLForQuery gera uma URL para consultar informações do usuário com base em uma URL de API dada e um ID de usuário.
// Se o ID do usuário estiver vazio ou inválido, a função retorna nil.
func getURLForQuery(apiURL, userID string) *string {
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	queryURL := fmt.Sprintf("%s/%s", strings.TrimRight(apiURL, "/"), userID)
	return &queryURL
}