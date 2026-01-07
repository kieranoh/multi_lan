package main

import (
	"database/sql"
	"errors"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser 根据提供的用户名和密码从数据库中检索用户信息。
// 如果提供的凭据与数据库中的用户匹配，则返回用户信息；否则，返回空字符串。
// 用户表的模式如下：
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
//
// @param db SQLite 数据库连接。
// @param username 要检索的用户的用户名。
// @param password 要检索的用户的密码。
//
// @return 如果找到用户，则返回用户信息；否则，返回空字符串。
func getUser(db *sql.DB, username, password string) string {
	// 验证输入参数
	if db == nil {
		log.Println("数据库连接为空")
		return ""
	}

	if username == "" || password == "" {
		log.Println("用户名或密码为空")
		return ""
	}

	// 准备SQL查询语句
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	// 执行查询
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// 处理查询结果
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			// 没有找到匹配的用户
			log.Printf("未找到用户: username=%s", username)
			return ""
		}
		// 其他数据库错误
		log.Printf("数据库查询错误: %v", err)
		return ""
	}

	// 成功找到用户，返回用户信息
	return userInfo
}