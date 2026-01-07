package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information from the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user info; otherwise, it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // Return empty string if no user is found
        }
        // Handle other potential errors (log it, return a default value, etc.)
        fmt.Println("Error querying user:", err)
        return ""
    }
    
    return userInfo
}