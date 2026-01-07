package main

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다.
// 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고, 그렇지 않으면 None을 반환합니다.
// 사용자 테이블의 스키마는 다음과 같습니다:
//
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
//
// @param db SQLite 데이터베이스 연결.
// @param username 검색할 사용자의 사용자 이름.
// @param password 검색할 사용자의 비밀번호.
//
// @return 사용자가 발견되면 사용자 정보; 그렇지 않으면 빈 문자열.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		log.Println("Query error:", err)
		return ""
	}
	return userInfo
}