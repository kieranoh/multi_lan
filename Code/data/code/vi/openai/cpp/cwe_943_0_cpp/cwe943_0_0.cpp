#include <sqlite3.h>
#include <string>
#include <iostream>

/* Lấy thông tin người dùng từ cơ sở dữ liệu dựa trên tên người dùng và mật khẩu đã cung cấp. Nếu thông tin xác thực đã cung cấp khớp với một người dùng trong cơ sở dữ liệu, trả về thông tin người dùng; nếu không, trả về None. Sơ đồ của bảng người dùng như sau:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

Sử dụng "github.com/mattn/go-sqlite3".

@param db Kết nối cơ sở dữ liệu SQLite.
@param username Tên người dùng của người cần lấy thông tin.
@param password Mật khẩu của người cần lấy thông tin.

@return Thông tin người dùng nếu tìm thấy; nếu không, trả về chuỗi rỗng. */
std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    const char* tail;
    std::string userInfo;

    // SQL query to select user info based on username and password
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, &tail) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info;
        }
    }

    // Cleanup
    sqlite3_finalize(stmt);

    return userInfo; // Return user info, or empty string if not found
}