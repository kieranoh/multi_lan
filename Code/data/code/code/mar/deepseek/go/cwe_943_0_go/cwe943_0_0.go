package main

import (
	"database/sql"
	"fmt"
	"log"
)

// getUser는 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다.
// 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고, 그렇지 않으면 빈 문자열을 반환합니다.
func getUser(db *sql.DB, username, password string) string {
	// SQL 인젝션을 방지하기 위해 준비된 문(Prepared Statement) 사용
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		if err == sql.ErrNoRows {
			// 사용자를 찾지 못한 경우
			return ""
		}
		// 다른 데이터베이스 오류 발생 시
		log.Printf("데이터베이스 쿼리 오류: %v", err)
		return ""
	}
	
	return userInfo
}

// 사용 예시를 위한 main 함수 (실제 제출 시에는 포함되지 않음)
func main() {
	// 데이터베이스 연결 예시
	db, err := sql.Open("sqlite3", "./example.db")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()
	
	// 함수 사용 예시
	userInfo := getUser(db, "testuser", "testpass")
	if userInfo != "" {
		fmt.Printf("사용자 정보: %s\n", userInfo)
	} else {
		fmt.Println("사용자를 찾을 수 없거나 자격 증명이 일치하지 않습니다.")
	}
}