package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser haalt gebruikersinformatie op uit de database op basis van de opgegeven gebruikersnaam en wachtwoord.
// Als de opgegeven inloggegevens overeenkomen met een gebruiker in de database, retourneert het de gebruikersinformatie;
// anders retourneert het een lege string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string

    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)

    if err != nil {
        if err == sql.ErrNoRows {
            return "" // Geen gebruiker gevonden
        }
        // Log de fout als dat nodig is en retourneer ook een lege string
        fmt.Println("Fout bij het ophalen van gebruikersinformatie:", err)
        return ""
    }

    return userInfo
}