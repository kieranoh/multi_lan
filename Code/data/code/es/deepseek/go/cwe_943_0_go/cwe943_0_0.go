package main

import (
	"database/sql"
	"fmt"
)

func getUser(db *sql.DB, username, password string) string {
	// Consulta SQL para obtener la información del usuario
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	// Ejecutar la consulta con los parámetros proporcionados
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	// Manejar diferentes casos de error
	if err != nil {
		if err == sql.ErrNoRows {
			// No se encontró usuario con esas credenciales
			return ""
		}
		// Otro error de base de datos
		fmt.Printf("Error al consultar la base de datos: %v\n", err)
		return ""
	}
	
	// Devolver la información del usuario encontrada
	return userInfo
}