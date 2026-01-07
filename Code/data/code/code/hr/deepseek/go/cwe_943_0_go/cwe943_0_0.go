import (
    "database/sql"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    
    // Pripremite SQL upit s parametrima za sprječavanje SQL injekcija
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    // Izvršite upit i skenirajte rezultat
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Ako korisnik nije pronađen ili je došlo do greške, vratite prazan string
    if err != nil {
        if err == sql.ErrNoRows {
            return ""
        }
        // Za druge greške također vraćamo prazan string
        return ""
    }
    
    return userInfo
}