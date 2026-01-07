#include <sqlite3.h>
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
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Förbered SQL-frågan
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Bind användarnamn och lösenord till frågan
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Utför frågan
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Kopiera användarinformationen
        }
    }

    // Rensa upp
    sqlite3_finalize(stmt);

    return userInfo; // Återvänd användarinformation eller NULL
}