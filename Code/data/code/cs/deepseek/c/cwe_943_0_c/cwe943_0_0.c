#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    
    // Připravíme SQL dotaz s parametry pro bezpečnost proti SQL injection
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        // Chyba při přípravě dotazu
        return NULL;
    }
    
    // Bind parametrů
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // Provedeme dotaz
    int step_result = sqlite3_step(stmt);
    
    if (step_result == SQLITE_ROW) {
        // Uživatel nalezen - zkopírujeme userInfo
        const char *userInfo = (const char *)sqlite3_column_text(stmt, 0);
        if (userInfo != NULL) {
            // Alokujeme paměť pro výsledek
            result = malloc(strlen(userInfo) + 1);
            if (result != NULL) {
                strcpy(result, userInfo);
            }
        }
    }
    
    // Vyčistíme statement
    sqlite3_finalize(stmt);
    
    return result;
}