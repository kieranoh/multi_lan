#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Získá informace o uživateli z databáze na základě zadaného uživatelského jména a hesla. 
   Pokud zadané údaje odpovídají uživateli v databázi, vrátí informace o uživateli; 
   jinak vrátí NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";
    char *userInfo = NULL;

    // Příprava SQL dotazu
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Chyba při přípravě dotazu
    }

    // Vázání parametrů
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Spuštění dotazu
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Duplikace řetězce pro vrácení
        }
    }

    // Uvolnění prostředků
    sqlite3_finalize(stmt);
    
    return userInfo; // Vrátí NULL nebo informace o uživateli
}