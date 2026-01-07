#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *tail;
    char *userInfo = NULL;

    // SQLクエリを準備する
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, &tail) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // プレースホルダに値をバインドする
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // SQLクエリを実行する
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // ユーザー情報を取得
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info);  // ユーザー情報をコピー
        }
    }

    // ステートメントを後片付けする
    sqlite3_finalize(stmt);

    return userInfo;  // ユーザー情報が見つからない場合はNULLが返ります
}