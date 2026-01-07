package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information from the database based on provided username and password.
// If the provided credentials match a user in the database, it returns the user information.
// Otherwise, it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := `SELECT userInfo FROM users WHERE username = ? AND password = ?`
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			// No user found with the provided credentials
			return ""
		}
		log.Println("Error querying the database:", err)
		return ""
	}
	return userInfo
}