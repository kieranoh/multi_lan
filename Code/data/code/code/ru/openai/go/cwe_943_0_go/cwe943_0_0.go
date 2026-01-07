package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser получает информацию о пользователе из базы данных на основе предоставленного имени пользователя и пароля.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string

	query := `SELECT userInfo FROM users WHERE username = ? AND password = ?`
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			// Пользователь не найден
			return ""
		}
		log.Fatal(err) // Обработка других ошибок
	}

	return userInfo
}