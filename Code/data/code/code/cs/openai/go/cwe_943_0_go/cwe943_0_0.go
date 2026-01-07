package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information from the database based on the provided username and password.
// If the credentials match a user in the database, it returns the user's information; otherwise, it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return "" // User not found
		}
		log.Fatalf("QueryRow failed: %v", err)
	}
	return userInfo
}