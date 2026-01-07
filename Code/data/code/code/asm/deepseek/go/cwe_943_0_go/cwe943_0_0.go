package main

import (
	"database/sql"
	"errors"
	"fmt"
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
		// 데이터베이스 오류의 경우에도 빈 문자열 반환
		return ""
	}

	return userInfo
}