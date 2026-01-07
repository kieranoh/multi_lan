#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    
    // SQLクエリの準備
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // パラメータのバインド
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // クエリの実行
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // ユーザー情報の取得
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // メモリの割り当てと文字列のコピー
            userInfo = malloc(strlen(info) + 1);
            if (userInfo != NULL) {
                strcpy(userInfo, info);
            }
        }
    }
    
    // ステートメントのクリーンアップ
    sqlite3_finalize(stmt);
    
    return userInfo;
}