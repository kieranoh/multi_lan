package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser استرجاع معلومات المستخدم من قاعدة البيانات بناءً على اسم المستخدم وكلمة المرور المقدمة.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	if err != nil {
		if err == sql.ErrNoRows {
			return "" // لا يوجد مستخدم مطابق
		}
		log.Fatal(err) // خطأ في الاستعلام
	}

	return userInfo // إرجاع معلومات المستخدم
}