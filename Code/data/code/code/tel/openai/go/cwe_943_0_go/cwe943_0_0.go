package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    var userInfo string

    // 쿼리 실행
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)

    if err != nil {
        if err == sql.ErrNoRows {
            // 사용자 정보가 없을 경우
            return ""
        }
        // 다른 오류 발생 시
        fmt.Println("Error querying user:", err)
        return ""
    }
    
    // 사용자 정보 반환
    return userInfo
}