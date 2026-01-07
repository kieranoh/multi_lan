package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser 根据提供的用户名和密码从数据库中检索用户信息。
// 如果提供的凭据与数据库中的用户匹配，则返回用户信息；否则，返回空字符串。
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"

	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			// 用户名或密码不匹配
			return ""
		}
		// 处理其他可能的错误
		log.Fatalf("Error querying user: %v", err)
	}

	return userInfo
}