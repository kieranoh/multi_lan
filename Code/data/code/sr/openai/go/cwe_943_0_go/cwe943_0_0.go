package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser preuzima informacije o korisniku iz baze podataka na osnovu datog korisničkog imena i lozinke.
// Ako se dati podaci poklapaju sa korisnikom u bazi, vraća informacije o korisniku; 
// u suprotnom, vraća prazan string.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	row := db.QueryRow(query, username, password)

	err := row.Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return "" // korisnik nije pronađen
		}
		log.Fatalf("Error querying user: %v", err)
	}

	return userInfo
}