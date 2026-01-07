#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

/* 提供されたユーザー名とパスワードに基づいて、データベースからユーザー情報を取得します。提供された資格情報がデータベース内のユーザーと一致する場合、ユーザー情報を返します。それ以外の場合は、Noneを返します。ユーザーテーブルのスキーマは以下の通りです:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLiteデータベース接続。
@param username 取得するユーザーのユーザー名。
@param password 取得するユーザーのパスワード。

@return ユーザーが見つかった場合はユーザー情報。それ以外の場合はNULL。 */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // SQL準備に失敗した場合
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        userInfo = strdup(info); // ユーザー情報を複製
    }

    sqlite3_finalize(stmt);
    return userInfo; // ユーザー情報またはNULLを返す
}