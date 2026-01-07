package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser searches for user information in the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user info; otherwise, it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    // Prepare the statement to prevent SQL injection
    stmt, err := db.Prepare(query)
    if err != nil {
        fmt.Println("Error preparing statement:", err)
        return ""
    }
    defer stmt.Close()

    // Query the database
    err = stmt.QueryRow(username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            // No user found
            return ""
        }
        // An error occurred while querying
        fmt.Println("Error querying user:", err)
        return ""
    }

    // Return the user info if found
    return userInfo
}