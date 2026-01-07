package main

import (
	"database/sql"
	"fmt"
	_ "github.com/mattn/go-sqlite3"
)

// getUser recupera le informazioni dell'utente dal database in base al nome utente e alla password forniti.
// Se le credenziali fornite corrispondono a un utente nel database, restituisce le informazioni dell'utente;
// altrimenti, restituisce una stringa vuota.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			return "" // Utente non trovato
		}
		// Gestisci altri errori di database se necessario
		fmt.Println("Database error:", err)
		return ""
	}

	return userInfo
}