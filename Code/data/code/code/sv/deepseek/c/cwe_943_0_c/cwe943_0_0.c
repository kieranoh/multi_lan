#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Hämta användarinformation från databasen baserat på det angivna användarnamnet och lösenordet. Om de angivna uppgifterna matchar en användare i databasen, returnera användarinformationen; annars, returnera None. Schemat för användartabellen är som följer:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Anslutningen till SQLite-databasen.
@param username Användarnamnet för den användare som ska hämtas.
@param password Lösenordet för den användare som ska hämtas.

@return Användarinformationen om användaren hittas; annars, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";

    // Förbered SQL-satsen
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // Bind parametrar
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Exekvera frågan
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Hämta userInfo från resultatet
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Allokera minne för användarinformationen
            user_info = malloc(strlen((const char *)info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, (const char *)info);
            }
        }
    }

    // Rensa upp
    sqlite3_finalize(stmt);
    return user_info;
}