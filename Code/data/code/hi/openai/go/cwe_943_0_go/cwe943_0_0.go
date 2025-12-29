package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information from the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user information; otherwise, it returns an empty string.
//
// @param db SQLite database connection.
// @param username The username of the user to retrieve.
// @param password The password of the user to retrieve.
//
// @return User information if found; otherwise, an empty string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return ""
        }
        fmt.Println("Error querying database:", err)
        return ""
    }
    
    return userInfo
}