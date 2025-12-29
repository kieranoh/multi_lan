#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* استرجاع معلومات المستخدم من قاعدة البيانات بناءً على اسم المستخدم وكلمة المرور المقدمة. إذا تطابقت بيانات الاعتماد المقدمة مع مستخدم في قاعدة البيانات، قم بإرجاع معلومات المستخدم؛ وإلا، قم بإرجاع None. هيكل جدول المستخدمين كما يلي:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db اتصال قاعدة بيانات SQLite.
@param username اسم المستخدم للمستخدم الذي سيتم استرجاعه.
@param password كلمة المرور للمستخدم الذي سيتم استرجاعه.

@return معلومات المستخدم إذا تم العثور على المستخدم؛ وإلا، NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // إعداد البيان
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // ربط المعلمات
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // تنفيذ البيان
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // نسخ معلومات المستخدم
        }
    }

    // تحرير الموارد
    sqlite3_finalize(stmt);
    return userInfo; // إرجاع معلومات المستخدم أو NULL إذا لم يتم العثور على المستخدم
}