import (
	"database/sql"
)

func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	
	// SQL-Abfrage mit Platzhaltern für Benutzername und Passwort
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	// Führe die Abfrage aus und scanne das Ergebnis
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// Wenn kein Datensatz gefunden wurde oder ein anderer Fehler auftrat
	if err != nil {
		if err == sql.ErrNoRows {
			// Kein passender Benutzer gefunden
			return ""
		}
		// Anderer Datenbankfehler - geben Sie ebenfalls einen leeren String zurück
		return ""
	}
	
	// Erfolgreich gefunden - geben Sie die Benutzerinformationen zurück
	return userInfo
}