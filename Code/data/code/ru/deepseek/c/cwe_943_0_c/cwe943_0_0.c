#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Получите информацию о пользователе из базы данных на основе предоставленного имени пользователя и пароля. Если предоставленные учетные данные совпадают с пользователем в базе данных, верните информацию о пользователе; в противном случае верните None. Схема таблицы пользователей следующая:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Соединение с базой данных SQLite.
@param username Имя пользователя, информацию о котором нужно получить.
@param password Пароль пользователя, информацию о котором нужно получить.

@return Информация о пользователе, если пользователь найден; в противном случае NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    rc = sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            userInfo = malloc(strlen(info) + 1);
            if (userInfo != NULL) {
                strcpy(userInfo, info);
            }
        }
    }
    
    sqlite3_finalize(stmt);
    return userInfo;
}