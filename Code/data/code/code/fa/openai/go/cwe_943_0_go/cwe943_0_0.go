package main

import (
	"database/sql"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

// getUser اطلاعات کاربر را از پایگاه داده بر اساس نام کاربری و رمز عبور ارائه شده بازیابی می‌کند.
// اگر اعتبارنامه ارائه شده با یک کاربر در پایگاه داده مطابقت داشته باشد، اطلاعات کاربر را برمی‌گرداند؛ 
// در غیر این صورت، یک رشته خالی را برمی‌گرداند.
func getUser(db *sql.DB, username, password string) string {
	var userInfo string
	query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
	err := db.QueryRow(query, username, password).Scan(&userInfo)

	if err != nil {
		if err == sql.ErrNoRows {
			return "" // کاربر پیدا نشد
		}
		log.Println("خطا در بازیابی اطلاعات کاربر:", err)
		return ""
	}

	return userInfo // بازگشت اطلاعات کاربر
}