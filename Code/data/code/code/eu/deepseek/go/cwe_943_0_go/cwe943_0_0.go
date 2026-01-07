import (
    "database/sql"
    "fmt"
)

func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    
    // Kontsulta prestatu erabiltzailea bilatzeko
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    // Kontsulta exekutatu eta emaitza irakurri
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Akatsak kudeatu
    if err != nil {
        if err == sql.ErrNoRows {
            // Ez da erabiltzailea aurkitu
            return ""
        }
        // Beste akats bat gertatu da
        fmt.Printf("Errorea kontsulta exekutatzean: %v\n", err)
        return ""
    }
    
    // Erabiltzailea aurkitu da, informazioa itzuli
    return userInfo
}