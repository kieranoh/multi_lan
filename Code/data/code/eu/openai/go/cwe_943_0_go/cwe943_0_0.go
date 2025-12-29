package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser erabiltzailearen informazioa datu-basean berariazko erabiltzaile-izena eta pasahitza erabiliz berreskuratu.
// Emandako akreditazioa datu-basean erabiltzaile batekin bat badator, itzuli erabiltzailearen informazioa;
// bestela, itzuli string huts bat.
// 
// @param db SQLite datu-basearen konexioa.
// @param username Berreskuratu beharreko erabiltzailearen erabiltzaile-izena.
// @param password Berreskuratu beharreko erabiltzailearen pasahitza.
// 
// @return Erabiltzailea aurkitzen bada, erabiltzailearen informazioa; bestela, string huts bat.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		log.Fatalf("Datu-basearen kontsulta huts egin da: %v", err)
	}
	return userInfo
}