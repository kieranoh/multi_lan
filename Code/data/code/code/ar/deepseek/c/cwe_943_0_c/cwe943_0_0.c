#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (!db || !username || !password) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    if (sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *userInfo = (const char *)sqlite3_column_text(stmt, 0);
        if (userInfo) {
            result = malloc(strlen(userInfo) + 1);
            if (result) {
                strcpy(result, userInfo);
            }
        }
    }
    
    sqlite3_finalize(stmt);
    return result;
}