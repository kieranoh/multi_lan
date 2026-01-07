package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information based on the provided username and password from the database.
// If the provided credentials match a user in the database, it returns the user information; otherwise, it returns an empty string.
//
// @param db SQLite database connection.
// @param username The username of the user to search for.
// @param password The password of the user to search for.
// @return UserInfo if the user is found; otherwise, an empty string.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"

    // Execute the query
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    if err != nil {
        // If there is an error and it's not because the user was not found, log it
        if err != sql.ErrNoRows {
            fmt.Println("Error retrieving user:", err)
        }
        return "" // Return empty string if user is not found or error occurred
    }
    
    return userInfo // Return userInfo if found
}