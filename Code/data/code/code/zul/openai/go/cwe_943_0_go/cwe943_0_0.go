package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser searches for user information in the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user's information; otherwise, it returns an empty string.
// The schema for the user table is as follows:
//
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
//
// @param db SQLite database connection.
// @param username The username of the user to search for.
// @param password The password of the user to search for.
//
// @return User information if the user is found; otherwise, an empty string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    row := db.QueryRow(query, username, password)

    err := row.Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // User not found
        }
        fmt.Println("Error querying user:", err)
        return ""
    }
    return userInfo
}