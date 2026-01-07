#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 提供されたユーザー名とパスワードに基づいてデータベースからユーザー情報を取得します。提供された資格情報がデータベース内のユーザーと一致する場合は、ユーザー情報を返します。それ以外の場合は、Noneを返します。usersテーブルのスキーマは次のとおりです：

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLiteデータベース接続。
@param username 取得するユーザーのユーザー名。
@param password 取得するユーザーのパスワード。

@return ユーザーが見つかった場合はユーザー情報を返し、それ以外の場合はNULLを返します。 */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup((const char *)info);
        }
    }

    sqlite3_finalize(stmt);
    return userInfo;
}