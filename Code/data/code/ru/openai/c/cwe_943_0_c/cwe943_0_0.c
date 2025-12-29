#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Подготовка SQL-запроса
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Ошибка при подготовке запроса
    }

    // Привязка параметров
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Выполнение запроса
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Копируем информацию пользователя
        }
    }

    // Освобождение ресурсов
    sqlite3_finalize(stmt);
    
    return userInfo; // Возвращаем информацию о пользователе или NULL
}