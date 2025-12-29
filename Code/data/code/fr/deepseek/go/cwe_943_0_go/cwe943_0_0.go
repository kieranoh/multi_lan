import (
    "database/sql"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    
    // Requête SQL pour récupérer les informations utilisateur
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    // Exécution de la requête avec les paramètres
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Si aucune ligne n'est trouvée ou si une erreur se produit, retourner une chaîne vide
    if err != nil {
        if err == sql.ErrNoRows {
            return ""
        }
        // En cas d'autres erreurs, retourner également une chaîne vide
        return ""
    }
    
    return userInfo
}