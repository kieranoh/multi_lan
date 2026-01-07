package main

import (
	"database/sql"
	"fmt"
	"log"
)

func getUser(db *sql.DB, username, password string) string {
	// SQL-fråga för att hämta användarinformation baserat på användarnamn och lösenord
	query := `SELECT userInfo FROM users WHERE username = ? AND password = ?`
	
	var userInfo string
	// Utför frågan och skanna resultatet
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		// Om ingen rad hittades eller annat fel uppstod
		if err == sql.ErrNoRows {
			// Returnera tom sträng om ingen användare hittades
			return ""
		}
		// Logga andra fel (i en riktig applikation skulle detta hanteras bättre)
		log.Printf("Fel vid hämtning av användare: %v", err)
		return ""
	}
	
	// Returnera användarinformationen om användaren hittades
	return userInfo
}