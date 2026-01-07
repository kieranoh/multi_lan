#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

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
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // SQL valmistelu epäonnistui
    }

    // Bindataan käyttäjänimi ja salasana kyselyyn
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Suoritetaan kysely
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Kopioidaan käyttäjätiedot
        }
    }

    // Vapautetaan resurssit
    sqlite3_finalize(stmt);
    
    return userInfo; // Palautetaan käyttäjätiedot tai NULL
}