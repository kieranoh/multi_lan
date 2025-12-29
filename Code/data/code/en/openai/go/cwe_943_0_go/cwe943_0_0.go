package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information from the database based on the provided username and password.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"

	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return "" // User not found
		}
		log.Println("Error querying database:", err)
		return ""
	}

	return userInfo // Return user information if found
}