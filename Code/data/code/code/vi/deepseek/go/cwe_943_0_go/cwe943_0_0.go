package main

import (
    "database/sql"
    _ "github.com/mattn/go-sqlite3"
)

func getUser(db *sql.DB, username, password string) string {
    // Kiểm tra đầu vào rỗng
    if username == "" || password == "" {
        return ""
    }
    
    var userInfo string
    // Truy vấn cơ sở dữ liệu để lấy thông tin người dùng
    query := "SELECT userInfo FROM users WHERE username = ? AND password = ?"
    err := db.QueryRow(query, username, password).Scan(&userInfo)
    
    // Xử lý lỗi và trường hợp không tìm thấy
    if err != nil {
        if err == sql.ErrNoRows {
            // Không tìm thấy người dùng với thông tin xác thực đã cho
            return ""
        }
        // Lỗi khác khi truy vấn cơ sở dữ liệu
        return ""
    }
    
    return userInfo
}