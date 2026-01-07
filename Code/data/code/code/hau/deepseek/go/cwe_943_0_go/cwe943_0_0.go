import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    // SQL 쿼리: username과 password가 모두 일치하는 사용자 검색
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    var userInfo string
    
    // 쿼리 실행
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // 오류 처리: 사용자를 찾지 못했거나 다른 오류 발생 시 빈 문자열 반환
    if err != nil {
        if err == sql.ErrNoRows {
            // 사용자를 찾지 못한 경우
            return ""
        }
        // 기타 데이터베이스 오류 발생 시
        fmt.Printf("Database error: %v\n", err)
        return ""
    }
    
    // 사용자 정보 반환
    return userInfo
}