import (
	"database/sql"
	"errors"
)

func getUser(db *sql.DB, username, password string) string {
	// 입력값 검증
	if username == "" || password == "" {
		return ""
	}

	// SQL 쿼리 준비
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// 사용자 정보가 없거나 오류 발생 시 빈 문자열 반환
	if err != nil {
		if errors.Is(err, sql.ErrNoRows) {
			return ""
		}
		// 다른 데이터베이스 오류의 경우에도 빈 문자열 반환
		return ""
	}
	
	return userInfo
}