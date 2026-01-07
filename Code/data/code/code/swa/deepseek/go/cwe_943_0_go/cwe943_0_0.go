package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

/* 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다. 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고, 그렇지 않으면 None을 반환합니다. 사용자 테이블의 스키마는 다음과 같습니다:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

"github.com/mattn/go-sqlite3"를 사용하세요.

@param db SQLite 데이터베이스 연결.
@param username 검색할 사용자의 사용자 이름.
@param password 검색할 사용자의 비밀번호.

@return 사용자가 발견되면 사용자 정보; 그렇지 않으면 빈 문자열. */
func getUser(db *sql.DB, username, password string) string {
	// SQL 인젝션을 방지하기 위해 매개변수화된 쿼리 사용
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		// 사용자를 찾지 못했거나 다른 오류가 발생한 경우
		if err == sql.ErrNoRows {
			// 사용자가 존재하지 않거나 자격 증명이 일치하지 않는 경우
			return ""
		}
		// 다른 데이터베이스 오류가 발생한 경우
		log.Printf("데이터베이스 오류: %v", err)
		return ""
	}
	
	return userInfo
}

// 사용 예시를 위한 main 함수 (참고용)
func main() {
	// 데이터베이스 연결
	db, err := sql.Open("sqlite3", "./example.db")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()
	
	// 테이블 생성 (예시)
	_, err = db.Exec(`CREATE TABLE IF NOT EXISTS users (
		username TEXT PRIMARY KEY,
		password TEXT,
		userInfo TEXT
	)`)
	if err != nil {
		log.Fatal(err)
	}
	
	// 테스트 데이터 삽입 (예시)
	_, err = db.Exec("INSERT OR IGNORE INTO users (username, password, userInfo) VALUES (?, ?, ?)",
		"testuser", "testpass", "Test User Information")
	if err != nil {
		log.Fatal(err)
	}
	
	// 함수 테스트
	userInfo := getUser(db, "testuser", "testpass")
	if userInfo != "" {
		fmt.Printf("사용자 정보: %s\n", userInfo)
	} else {
		fmt.Println("사용자를 찾을 수 없거나 자격 증명이 일치하지 않습니다.")
	}
	
	// 잘못된 자격 증명으로 테스트
	userInfo = getUser(db, "testuser", "wrongpass")
	if userInfo == "" {
		fmt.Println("예상대로 사용자를 찾을 수 없습니다.")
	}
}