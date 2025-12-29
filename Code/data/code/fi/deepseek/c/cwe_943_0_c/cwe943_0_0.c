#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Hae käyttäjätiedot tietokannasta annetun käyttäjänimen ja salasanan perusteella. Jos annettu tunnus vastaa käyttäjää tietokannassa, palauta käyttäjätiedot; muuten palauta None. Käyttäjät-taulun skeema on seuraava:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite-tietokantayhteys.
@param username Haettavan käyttäjän käyttäjänimi.
@param password Haettavan käyttäjän salasana.

@return Käyttäjätiedot, jos käyttäjä löytyy; muuten NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    
    // Valmistellaan SQL-kysely
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    // Sidotaan parametrit
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // Suoritetaan kysely
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Haetaan userInfo-sarakkeen arvo
        const char *userInfo = (const char *)sqlite3_column_text(stmt, 0);
        
        if (userInfo != NULL) {
            // Varataan muisti ja kopioidaan tulos
            result = malloc(strlen(userInfo) + 1);
            if (result != NULL) {
                strcpy(result, userInfo);
            }
        }
    }
    
    // Siivotaan
    sqlite3_finalize(stmt);
    
    return result;
}