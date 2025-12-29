package main

import (
	"database/sql"
	"fmt"
	"log"
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
	
	// 쿼리 실행 및 결과 스캔
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			// 사용자를 찾을 수 없음
			log.Printf("사용자 '%s'를 찾을 수 없거나 비밀번호가 일치하지 않습니다\n", username)
			return ""
		}
		// 다른 데이터베이스 오류
		log.Printf("데이터베이스 쿼리 오류: %v\n", err)
		return ""
	}

	// 성공적으로 사용자 정보 반환
	return userInfo
}