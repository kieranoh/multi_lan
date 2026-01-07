package main

import (
	"database/sql"
	"errors"
)

func getUser(db *sql.DB, username, password string) string {
	if db == nil {
		return ""
	}

	if username == "" || password == "" {
		return ""
	}

	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return ""
		}
		return ""
	}

	return userInfo
}