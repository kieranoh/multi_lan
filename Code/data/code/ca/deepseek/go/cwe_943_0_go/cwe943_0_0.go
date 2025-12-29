import (
	"database/sql"
)

func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		// En cas d'altres errors, també retornem cadena buida
		return ""
	}
	return userInfo
}