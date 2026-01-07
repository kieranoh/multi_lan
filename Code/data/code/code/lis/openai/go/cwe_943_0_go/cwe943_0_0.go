package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser는 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다.
// 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고,
// 그렇지 않으면 빈 문자열을 반환합니다.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string

    // SQL 쿼리를 준비합니다.
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    // 쿼리를 실행합니다.
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // 사용자가 발견되지 않음
        }
        // 다른 오류가 발생한 경우, 로그를 출력하고 빈 문자열을 반환합니다.
        fmt.Println("Error querying user:", err)
        return ""
    }

    return userInfo // 사용자 정보를 반환합니다.
}