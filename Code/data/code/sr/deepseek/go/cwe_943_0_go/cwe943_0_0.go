import (
    "database/sql"
)

func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    
    // Pripremimo SQL upit sa parametrizovanim upitom radi bezbednosti
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    // Izvršimo upit i skeniramo rezultat
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Ako nema rezultata ili je došlo do greške, vratimo prazan string
    if err != nil {
        if err == sql.ErrNoRows {
            // Nije pronađen korisnik sa datim kredencijalima
            return ""
        }
        // Došlo je do druge greške pri izvršavanju upita
        return ""
    }
    
    // Vratimo pronađene informacije o korisniku
    return userInfo
}