package main

import (
	"database/sql"
	"fmt"
	"log"
)

func getUser(db *sql.DB, username, password string) string {
	// SQL-kysely käyttäjän tietojen hakemiseksi
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		if err == sql.ErrNoRows {
			// Käyttäjää ei löytynyt
			return ""
		}
		// Jokin muu virhe tapahtui
		log.Printf("Virhe käyttäjätietojen haussa: %v", err)
		return ""
	}
	
	return userInfo
}