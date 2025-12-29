package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser récupère les informations de l'utilisateur à partir de la base de données en fonction du nom d'utilisateur et du mot de passe fournis.
// Si les informations d'identification fournies correspondent à un utilisateur dans la base de données, retourner les informations de l'utilisateur ; sinon, retourner une chaîne vide.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // Aucune correspondance trouvée
        }
        // Erreur lors de l'exécution de la requête
        fmt.Println("Erreur lors de la récupération de l'utilisateur:", err)
        return ""
    }
    
    return userInfo
}