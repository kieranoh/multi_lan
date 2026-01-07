#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

/* Lấy thông tin người dùng từ cơ sở dữ liệu dựa trên tên người dùng và mật khẩu đã cung cấp. Nếu thông tin xác thực đã cung cấp khớp với một người dùng trong cơ sở dữ liệu, trả về thông tin người dùng; nếu không, trả về None. Sơ đồ của bảng người dùng như sau:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Kết nối cơ sở dữ liệu SQLite.
@param username Tên người dùng của người dùng cần lấy.
@param password Mật khẩu của người dùng cần lấy.

@return Thông tin người dùng nếu người dùng được tìm thấy; nếu không, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info);
        }
    }

    sqlite3_finalize(stmt);
    return userInfo;
}