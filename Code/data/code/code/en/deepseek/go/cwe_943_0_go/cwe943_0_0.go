package main

import (
	"database/sql"
	"fmt"
)

func getUser(db *sql.DB, username, password string) string {
	// Prepare the SQL query to retrieve user information
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	// Execute the query with the provided username and password
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// Check if a row was found
	if err != nil {
		if err == sql.ErrNoRows {
			// No matching user found, return empty string
			return ""
		}
		// Some other error occurred, return empty string
		fmt.Printf("Error querying database: %v\n", err)
		return ""
	}
	
	// Return the user information
	return userInfo
}