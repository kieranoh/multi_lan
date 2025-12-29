import (
	"database/sql"
)

func getUser(db *sql.DB, username, password string) string {
	// Ellenőrizzük, hogy a kapcsolat érvényes-e
	if db == nil {
		return ""
	}

	// SQL lekérdezés a felhasználó lekéréséhez
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// Ha nem található felhasználó vagy hiba történt, üres stringet adunk vissza
	if err != nil {
		if err == sql.ErrNoRows {
			// Nincs ilyen felhasználó a megadott hitelesítő adatokkal
			return ""
		}
		// Egyéb adatbázis hiba esetén is üres stringet adunk vissza
		return ""
	}
	
	return userInfo
}