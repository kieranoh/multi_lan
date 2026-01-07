import (
	"database/sql"
)

func getUser(db *sql.DB, username, password string) string {
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		// در صورت بروز خطای دیگر، یک رشته خالی برگردانید
		return ""
	}
	
	return userInfo
}