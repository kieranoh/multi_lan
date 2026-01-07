package main

import (
	"database/sql"
	"errors"
)

func getUser(db *sql.DB, username, password string) string {
	if db == nil {
		return ""
	}

	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return ""
		}
		return ""
	}

	return userInfo
}