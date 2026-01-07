#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";

    // プリペアドステートメントの準備
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // パラメータのバインド
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }

    // クエリの実行
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // ユーザー情報の取得
        const char *result = (const char *)sqlite3_column_text(stmt, 0);
        if (result != NULL) {
            // メモリを割り当ててユーザー情報をコピー
            user_info = malloc(strlen(result) + 1);
            if (user_info != NULL) {
                strcpy(user_info, result);
            }
        }
    }

    // ステートメントの解放
    sqlite3_finalize(stmt);
    return user_info;
}