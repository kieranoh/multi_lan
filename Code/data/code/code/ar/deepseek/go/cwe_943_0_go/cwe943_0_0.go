package main

import (
	"database/sql"
	"fmt"
	"log"
	_ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
	// استعلام SQL لاسترجاع معلومات المستخدم بناءً على اسم المستخدم وكلمة المرور
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	
	var userInfo string
	err := db.QueryRow(query, username, password).Scan(&userInfo)
	
	if err != nil {
		if err == sql.ErrNoRows {
			// لم يتم العثور على مستخدم مطابق
			return ""
		}
		// خطأ في قاعدة البيانات
		log.Printf("خطأ في استعلام قاعدة البيانات: %v", err)
		return ""
	}
	
	return userInfo
}