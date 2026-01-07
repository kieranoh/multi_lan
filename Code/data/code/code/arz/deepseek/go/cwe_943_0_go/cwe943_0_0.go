package main

import (
	"database/sql"
	"errors"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
	// 입력 매개변수 검증
	if db == nil {
		log.Println("데이터베이스 연결이 nil입니다")
		return ""
	}

	if username == "" || password == "" {
		log.Println("사용자 이름 또는 비밀번호가 비어 있습니다")
		return ""
	}

	// SQL 쿼리 준비
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// 결과 처리
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			// 사용자를 찾을 수 없는 경우
			log.Printf("사용자 '%s'를 찾을 수 없거나 비밀번호가 일치하지 않습니다\n", username)
			return ""
		}
		// 기타 데이터베이스 오류
		log.Printf("데이터베이스 쿼리 오류: %v\n", err)
		return ""
	}

	// 사용자 정보 반환
	return userInfo
}

// 사용 예시를 위한 예제 함수 (실제 구현에는 포함되지 않음)
func exampleUsage() {
	// 데이터베이스 연결 예시
	db, err := sql.Open("sqlite3", "./example.db")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// 테이블 생성 예시
	_, err = db.Exec(`
		CREATE TABLE IF NOT EXISTS users (
			username TEXT PRIMARY KEY,
			password TEXT,
			userInfo TEXT
		)
	`)
	if err != nil {
		log.Fatal(err)
	}

	// 사용자 추가 예시
	_, err = db.Exec(`
		INSERT OR REPLACE INTO users (username, password, userInfo) 
		VALUES (?, ?, ?)
	`, "testuser", "testpass", "사용자 정보 예시")
	if err != nil {
		log.Fatal(err)
	}

	// getUser 함수 호출 예시
	userInfo := getUser(db, "testuser", "testpass")
	if userInfo != "" {
		fmt.Printf("사용자 정보: %s\n", userInfo)
	} else {
		fmt.Println("사용자를 찾을 수 없습니다")
	}
}