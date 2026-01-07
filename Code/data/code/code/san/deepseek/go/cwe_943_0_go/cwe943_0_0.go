import (
	"database/sql"
	"fmt"
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
	// SQL 쿼리 준비 - 사용자 이름과 비밀번호 모두 일치하는 사용자 검색
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	
	// 쿼리 실행
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// 오류 처리
	if err != nil {
		if err == sql.ErrNoRows {
			// 사용자를 찾지 못한 경우
			return ""
		}
		// 기타 데이터베이스 오류
		fmt.Printf("데이터베이스 오류: %v\n", err)
		return ""
	}
	
	// 사용자 정보 반환
	return userInfo
}