#include <sqlite3.h>
#include <stdio.h>
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
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Chuẩn bị câu lệnh SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // Ràng buộc tham số
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // Thực thi truy vấn
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Lấy dữ liệu userInfo
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Cấp phát bộ nhớ và sao chép chuỗi
            user_info = malloc(strlen(info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, info);
            }
        }
    }
    
    // Giải phóng tài nguyên
    sqlite3_finalize(stmt);
    
    return user_info;
}