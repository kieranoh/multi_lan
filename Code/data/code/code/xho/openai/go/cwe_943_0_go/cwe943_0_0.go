package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser searches for user information in the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user information; otherwise, it returns an empty string.
// The users table schema is as follows:
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"

    row := db.QueryRow(query, username, password)
    err := row.Scan(&userInfo)

    if err != nil {
        if err == sql.ErrNoRows {
            return "" // No user found
        }
        // Handle other potential errors if necessary
        fmt.Println("Error querying user:", err)
        return ""
    }

    return userInfo // Return user information if found
}