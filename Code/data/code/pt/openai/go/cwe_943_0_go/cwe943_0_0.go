package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser recupera as informações do usuário do banco de dados com base no nome de usuário e na senha fornecidos.
// Se as credenciais fornecidas corresponderem a um usuário no banco de dados, retorna as informações do usuário;
// caso contrário, retorna uma string vazia.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string

	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		log.Printf("Erro ao consultar o banco de dados: %v", err)
		return ""
	}

	return userInfo
}