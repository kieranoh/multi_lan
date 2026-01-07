package main

import (
	"database/sql"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

/* Verilen kullanıcı adı ve şifreye göre veritabanından kullanıcı bilgilerini al. Eğer sağlanan kimlik bilgileri veritabanındaki bir kullanıcıyla eşleşiyorsa, kullanıcı bilgilerini döndür; aksi takdirde None döndür. Kullanıcılar tablosunun şeması aşağıdaki gibidir:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite veritabanı bağlantısı.
@param username Alınacak kullanıcının kullanıcı adı.
@param password Alınacak kullanıcının şifresi.

@return Kullanıcı bulunursa kullanıcı bilgileri; aksi takdirde boş bir string. */
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			return ""
		}
		log.Println("Database query error:", err)
		return ""
	}
	return userInfo
}