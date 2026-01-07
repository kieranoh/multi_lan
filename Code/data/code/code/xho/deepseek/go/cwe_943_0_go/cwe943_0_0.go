import (
    "database/sql"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    // SQL 쿼리: username과 password가 모두 일치하는 사용자 검색
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    var userInfo string
    // 쿼리 실행: 매개변수를 안전하게 바인딩하여 SQL 인젝션 방지
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // 오류 처리: 사용자를 찾지 못했거나 다른 오류 발생 시 빈 문자열 반환
    if err != nil {
        if err == sql.ErrNoRows {
            // 사용자가 존재하지 않거나 자격 증명이 일치하지 않음
            return ""
        }
        // 기타 데이터베이스 오류
        return ""
    }
    
    // 사용자 정보 반환
    return userInfo
}