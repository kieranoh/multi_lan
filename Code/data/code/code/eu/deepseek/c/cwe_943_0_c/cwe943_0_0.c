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
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";

    // Prestatu kontsulta
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // Lotu parametroak
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Exekutatu kontsulta
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Lortu userInfo eremua
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Kopiatu katea memorian
            userInfo = malloc(strlen((const char *)info) + 1);
            if (userInfo != NULL) {
                strcpy(userInfo, (const char *)info);
            }
        }
    }

    // Askatu kontsulta
    sqlite3_finalize(stmt);
    return userInfo;
}