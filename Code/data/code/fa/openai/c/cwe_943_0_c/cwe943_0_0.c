#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* اطلاعات کاربر را از پایگاه داده بر اساس نام کاربری و رمز عبور ارائه شده بازیابی کنید. اگر اعتبارنامه ارائه شده با کاربری در پایگاه داده مطابقت داشته باشد، اطلاعات کاربر را برگردانید؛ در غیر این صورت، None را برگردانید. ساختار جدول کاربران به صورت زیر است:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db اتصال پایگاه داده SQLite.
@param username نام کاربری کاربری که باید بازیابی شود.
@param password رمز عبور کاربری که باید بازیابی شود.

@return اطلاعات کاربر در صورت یافتن کاربر؛ در غیر این صورت، NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // آماده‌سازی بیان SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // قرار دادن پارامترها
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    char *userInfo = NULL;

    // اجرای بیان و بازیابی داده‌ها
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // کپی کردن اطلاعات کاربر
        }
    }

    // آزادسازی منابع
    sqlite3_finalize(stmt);

    return userInfo; // بازگشت اطلاعات کاربر یا NULL
}