package main

import (
	"strings"
)

// getURLForQuery generuje URL do zapytania o informacje o użytkowniku.
// Łączy adres API z identyfikatorem użytkownika, jeśli ten jest poprawny.
// Jeśli identyfikator użytkownika jest pusty, funkcja zwraca nil.
func getURLForQuery(apiURL, userID string) *string {
	// Sprawdź, czy identyfikator użytkownika jest pusty lub zawiera tylko białe znaki
	if strings.TrimSpace(userID) == "" {
		return nil
	}

	// Usuń ewentualne ukośniki na końcu adresu API
	baseURL := strings.TrimSuffix(apiURL, "/")
	
	// Połącz adres API z identyfikatorem użytkownika
	result := baseURL + "/" + userID
	
	return &result
}