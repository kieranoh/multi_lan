package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser hämtar användarinformation från databasen baserat på det angivna användarnamnet och lösenordet.
// Om de angivna uppgifterna matchar en användare i databasen, returnera användarinformationen; annars, returnera en tom sträng.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string

    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)

    if err != nil {
        if err == sql.ErrNoRows {
            return "" // Ingen användare hittades
        }
        fmt.Println("Fel vid hämtning av användardata:", err)
        return "" // Returnera tom sträng vid fel
    }

    return userInfo
}