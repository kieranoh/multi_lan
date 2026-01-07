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
    
    // Prepare statement to avoid SQL injection
    stmt, err := db.Prepare(query)
    if err != nil {
        fmt.Println("Error preparing statement:", err)
        return ""
    }
    defer stmt.Close()

    // Execute the query with the provided username and password
    err = stmt.QueryRow(username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            // No user found
            return ""
        }
        fmt.Println("Error executing query:", err)
        return ""
    }

    // Return the user information if found
    return userInfo
}