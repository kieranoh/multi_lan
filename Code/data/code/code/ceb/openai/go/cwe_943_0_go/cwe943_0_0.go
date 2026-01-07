package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser searches for user information in the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user information,
// otherwise, it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string

	// Prepare the SQL statement for execution
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		// If there's an error and it's not sql.ErrNoRows, log it
		if err != sql.ErrNoRows {
			log.Printf("Error querying user: %v", err)
		}
		// If no user is found, userInfo will be an empty string
		return ""
	}

	return userInfo
}