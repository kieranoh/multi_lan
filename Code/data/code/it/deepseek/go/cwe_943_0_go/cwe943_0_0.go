import (
    "database/sql"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    // Query per recuperare le informazioni dell'utente
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    var userInfo string
    // Esegui la query con i parametri forniti
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Se non viene trovato alcun utente o si verifica un errore, restituisci stringa vuota
    if err != nil {
        if err == sql.ErrNoRows {
            // Nessun utente trovato con le credenziali fornite
            return ""
        }
        // Altri errori (log, ma restituisci comunque stringa vuota)
        return ""
    }
    
    // Restituisci le informazioni dell'utente
    return userInfo
}