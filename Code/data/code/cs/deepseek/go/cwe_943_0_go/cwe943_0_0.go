import (
    "database/sql"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    // SQL dotaz pro získání informací o uživateli
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    var userInfo string
    // Spuštění dotazu s parametry
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Pokud nenalezen uživatel nebo chyba, vrátí prázdný řetězec
    if err != nil {
        if err == sql.ErrNoRows {
            // Žádný uživatel nebyl nalezen
            return ""
        }
        // Jiná chyba při dotazu
        return ""
    }
    
    // Uživatel nalezen, vrátí informace
    return userInfo
}