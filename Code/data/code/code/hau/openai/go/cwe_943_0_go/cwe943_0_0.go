package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser retrieves user information based on the provided username and password.
// If the provided credentials match a user in the database, it returns the user info;
// otherwise, it returns an empty string.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string

	// Prepare the SQL query to select user information
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			// No matching user found
			return ""
		}
		// Log any other errors encountered while querying
		log.Printf("Error querying database: %v", err)
		return ""
	}

	return userInfo
}

func main() {
	// Example usage of getUser function
	database, err := sql.Open("sqlite3", "./users.db")
	if err != nil {
		log.Fatal(err)
	}
	defer database.Close()

	username := "testuser"
	password := "testpass"
	userInfo := getUser(database, username, password)

	if userInfo != "" {
		fmt.Printf("User info: %s\n", userInfo)
	} else {
		fmt.Println("User not found or invalid credentials.")
	}
}