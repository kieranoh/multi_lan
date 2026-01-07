package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

/*
Hae käyttäjätiedot tietokannasta annetun käyttäjänimen ja salasanan perusteella. 
Jos annettu tunnus vastaa käyttäjää tietokannassa, palauta käyttäjätiedot; 
muuten palauta None. Käyttäjät-taulun skeema on seuraava:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite-tietokantayhteys.
@param username Haettavan käyttäjän käyttäjänimi.
@param password Haettavan käyttäjän salasana.

@return Käyttäjätiedot, jos käyttäjä löytyy; muuten tyhjää merkkijonoa.
*/
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return ""
        }
        fmt.Printf("Error querying user: %v\n", err)
        return ""
    }
    return userInfo
}