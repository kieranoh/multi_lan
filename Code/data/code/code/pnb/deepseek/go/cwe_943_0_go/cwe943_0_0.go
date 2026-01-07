package main

import (
	"database/sql"
	"fmt"
	"log"
	"strings"

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
	if db == nil {
		log.Println("데이터베이스 연결이 nil입니다")
		return ""
	}

	// SQL 인젝션 방지를 위해 입력값 검증
	username = strings.TrimSpace(username)
	password = strings.TrimSpace(password)
	
	if username == "" || password == "" {
		log.Println("사용자 이름 또는 비밀번호가 비어 있습니다")
		return ""
	}

	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			// 사용자를 찾을 수 없음
			log.Printf("사용자를 찾을 수 없습니다: %s\n", username)
			return ""
		}
		// 다른 데이터베이스 오류
		log.Printf("데이터베이스 쿼리 오류: %v\n", err)
		return ""
	}

	return userInfo
}

// 사용 예시를 위한 main 함수 (실제 사용 시 필요에 따라 조정)
func main() {
	// 데이터베이스 연결 예시
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
	_, err = db.Exec("INSERT OR IGNORE INTO users(username, password, userInfo) VALUES(?, ?, ?)", 
		"testuser", "testpass", "테스트 사용자 정보")
	if err != nil {
		log.Fatal(err)
	}

	// getUser 함수 테스트
	userInfo := getUser(db, "testuser", "testpass")
	if userInfo != "" {
		fmt.Printf("사용자 정보: %s\n", userInfo)
	} else {
		fmt.Println("사용자를 찾을 수 없습니다")
	}

	// 잘못된 자격 증명으로 테스트
	userInfo = getUser(db, "wronguser", "wrongpass")
	if userInfo == "" {
		fmt.Println("잘못된 자격 증명 - 예상대로 빈 문자열 반환")
	}
}