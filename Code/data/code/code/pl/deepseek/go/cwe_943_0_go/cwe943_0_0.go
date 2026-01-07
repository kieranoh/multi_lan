package main

import (
	"database/sql"
	"fmt"
)

func getUser(db *sql.DB, username, password string) string {
	// Zapytanie SQL do pobrania informacji o użytkowniku na podstawie nazwy użytkownika i hasła
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	// Wykonanie zapytania z parametrami
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// Sprawdzenie, czy użytkownik został znaleziony
	if err != nil {
		if err == sql.ErrNoRows {
			// Brak pasującego użytkownika - zwróć pusty ciąg
			return ""
		}
		// Inny błąd - zwróć pusty ciąg (można też zalogować błąd w praktycznym zastosowaniu)
		return ""
	}
	
	// Zwróć informacje o użytkowniku
	return userInfo
}