#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Recupera le informazioni dell'utente dal database in base al nome utente e alla password forniti. Se le credenziali fornite corrispondono a un utente nel database, restituisci le informazioni dell'utente; altrimenti, restituisci None. Lo schema della tabella degli utenti è il seguente:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db La connessione al database SQLite.
@param username Il nome utente dell'utente da recuperare.
@param password La password dell'utente da recuperare.

@return Le informazioni dell'utente se l'utente viene trovato; altrimenti, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepara l'istruzione SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Bind dei parametri
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Esegui l'istruzione e recupera i risultati
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info);
        }
    }

    // Finalizza l'istruzione
    sqlite3_finalize(stmt);

    return userInfo;
}