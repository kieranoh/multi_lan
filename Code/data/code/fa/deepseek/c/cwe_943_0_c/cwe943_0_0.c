#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * اطلاعات کاربر را از پایگاه داده بر اساس نام کاربری و رمز عبور ارائه شده بازیابی کنید.
 * اگر اعتبارنامه ارائه شده با کاربری در پایگاه داده مطابقت داشته باشد، اطلاعات کاربر را برگردانید؛
 * در غیر این صورت، NULL را برگردانید.
 * 
 * @param db اتصال پایگاه داده SQLite.
 * @param username نام کاربری کاربری که باید بازیابی شود.
 * @param password رمز عبور کاربری که باید بازیابی شود.
 * 
 * @return اطلاعات کاربر در صورت یافتن کاربر؛ در غیر این صورت، NULL.
 *         حافظه برگشتی باید توسط فراخواننده آزاد شود.
 */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // آماده‌سازی عبارت SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // اتصال پارامترها
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // اجرای کوئری
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // دریافت userInfo از ستون اول
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // تخصیص حافظه و کپی رشته
            userInfo = strdup((const char *)info);
        }
    }
    
    // پاکسازی
    sqlite3_finalize(stmt);
    
    return userInfo;
}