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
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Prepara la query SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    // Associa i parametri alla query
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    if (sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // Esegui la query
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        // Recupera le informazioni dell'utente
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Alloca memoria per la stringa risultato
            user_info = malloc(strlen(info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, info);
            }
        }
    }
    
    // Pulisci la dichiarazione preparata
    sqlite3_finalize(stmt);
    
    return user_info;
}