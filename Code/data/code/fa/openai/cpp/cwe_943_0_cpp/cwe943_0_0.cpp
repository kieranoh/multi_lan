#include <sqlite3.h>
#include <string>
#include <stdexcept>

/**
 * @brief اطلاعات کاربر را از پایگاه داده بر اساس نام کاربری و رمز عبور ارائه شده بازیابی کنید.
 * 
 * اگر اعتبارنامه ارائه شده با یک کاربر در پایگاه داده مطابقت داشته باشد، اطلاعات کاربر را برگردانید؛ در غیر این صورت، None را برگردانید.
 * 
 * @param db اتصال پایگاه داده SQLite.
 * @param username نام کاربری کاربری که باید بازیابی شود.
 * @param password رمز عبور کاربری که باید بازیابی شود.
 * 
 * @return اطلاعات کاربر در صورت یافتن کاربر؛ در غیر این صورت، یک رشته خالی.
 */
std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;

    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // آماده‌سازی عبارت SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }

    // بایند کردن پارامترها
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // اجرای عبارت و بازیابی اطلاعات
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* info = sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = reinterpret_cast<const char*>(info);
        }
    }

    // آزادسازی منابع
    sqlite3_finalize(stmt);
    
    return userInfo; // اگر کاربر یافت نشود، رشته خالی برمی‌گردد
}