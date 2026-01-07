package main

import (
	"database/sql"
	"fmt"
	"log"
)

// Verilen kullanıcı adı ve şifreye göre veritabanından kullanıcı bilgilerini al.
// Eğer sağlanan kimlik bilgileri veritabanındaki bir kullanıcıyla eşleşiyorsa,
// kullanıcı bilgilerini döndür; aksi takdirde boş string döndür.
// Kullanıcılar tablosunun şeması aşağıdaki gibidir:
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
// @param db SQLite veritabanı bağlantısı.
// @param username Alınacak kullanıcının kullanıcı adı.
// @param password Alınacak kullanıcının şifresi.
// @return Kullanıcı bulunursa kullanıcı bilgileri; aksi takdirde boş bir string.
func getUser(db *sql.DB, username, password string) string {
	// SQL sorgusu: kullanıcı adı ve şifre eşleşen kullanıcının userInfo'sunu al
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	
	// Sorguyu çalıştır
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		// Eğer kullanıcı bulunamazsa veya başka bir hata oluşursa
		if err == sql.ErrNoRows {
			// Kullanıcı bulunamadı, boş string döndür
			return ""
		}
		// Diğer veritabanı hataları için log kaydı (gerçek uygulamada daha iyi hata yönetimi)
		log.Printf("Veritabanı hatası: %v", err)
		return ""
	}
	
	// Kullanıcı bulundu, userInfo'yu döndür
	return userInfo
}