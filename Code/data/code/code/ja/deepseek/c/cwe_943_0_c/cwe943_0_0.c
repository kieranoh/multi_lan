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
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *user_info = NULL;

    // プリペアドステートメントを準備
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // パラメータをバインド
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // クエリを実行
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // ユーザー情報を取得
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // メモリを割り当ててコピー
            user_info = malloc(strlen(info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, info);
            }
        }
    }

    // ステートメントを解放
    sqlite3_finalize(stmt);

    return user_info;
}