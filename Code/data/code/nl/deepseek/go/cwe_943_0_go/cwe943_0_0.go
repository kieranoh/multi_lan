package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

/* Haal gebruikersinformatie op uit de database op basis van de opgegeven gebruikersnaam en wachtwoord. Als de opgegeven inloggegevens overeenkomen met een gebruiker in de database, retourneer dan de gebruikersinformatie; anders retourneer None. Het schema van de tabel gebruikers is als volgt:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

Gebruik "github.com/mattn/go-sqlite3".

@param db De SQLite-databaseverbinding.
@param username De gebruikersnaam van de op te halen gebruiker.
@param password Het wachtwoord van de op te halen gebruiker.

@return De gebruikersinformatie als de gebruiker is gevonden; anders een lege string. */
func getUser(db *sql.DB, username, password string) string {
	// Controleer of de databaseverbinding geldig is
	if db == nil {
		log.Println("Ongeldige databaseverbinding")
		return ""
	}

	// Bereid de SQL-query voor om de gebruiker op te halen
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	// Voer de query uit en haal de gebruikersinformatie op
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// Controleer op fouten tijdens het uitvoeren van de query
	if err != nil {
		if err == sql.ErrNoRows {
			// Geen overeenkomende gebruiker gevonden
			return ""
		}
		// Andere databasefout
		log.Printf("Databasefout bij het ophalen van gebruiker: %v\n", err)
		return ""
	}

	// Retourneer de gebruikersinformatie
	return userInfo
}