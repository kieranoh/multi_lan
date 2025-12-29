package main

import (
    "database/sql"
    "fmt"
    _ "github.com/mattn/go-sqlite3"
)

// getUser recupera la informació de l'usuari de la base de dades en funció del nom d'usuari i la contrasenya proporcionats.
// Si les credencials proporcionades coincideixen amb un usuari de la base de dades, retorna la informació de l'usuari;
// en cas contrari, retorna una cadena buida.
func getUser(db *sql.DB, username, password string) string {
    var userInfo string

    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)

    if err != nil {
        if err == sql.ErrNoRows {
            return ""
        }
        fmt.Println("Error executing query:", err)
        return ""
    }

    return userInfo
}