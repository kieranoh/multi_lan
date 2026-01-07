package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser searches for user information in the database based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user info; otherwise, it returns an empty string.
// The schema for the user table is as follows:
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := `SELECT userInfo FROM users WHERE username = ? AND password = ?`
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		log.Println("Error querying user:", err)
		return ""
	}

	return userInfo
}