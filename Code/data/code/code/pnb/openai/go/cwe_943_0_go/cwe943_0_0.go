package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser searches for user information in the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user information,
// otherwise it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // User not found
        }
        // Handle other errors (optional)
        fmt.Println("Error querying user:", err)
        return ""
    }
    return userInfo
}