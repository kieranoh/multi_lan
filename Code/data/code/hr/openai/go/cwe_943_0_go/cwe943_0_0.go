package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser preuzima informacije o korisniku iz baze podataka na temelju pruženog korisničkog imena i lozinke.
// Ako se pruženi podaci podudaraju s korisnikom u bazi podataka, vraća informacije o korisniku; inače, vraća prazan niz.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string

	// Upit za dohvaćanje informacija o korisniku na temelju korisničkog imena i lozinke
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			// Ako nema podudaranja, vraćamo prazan niz
			return ""
		}
		// U slučaju greške, logiramo grešku
		log.Printf("Error querying user: %v", err)
		return ""
	}

	return userInfo
}