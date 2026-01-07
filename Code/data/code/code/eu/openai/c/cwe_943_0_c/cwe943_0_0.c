#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Erabiltzailearen informazioa datu-basean lortu emandako erabiltzaile-izena eta pasahitza oinarrituta. Emandako akreditazioa datu-basean erabiltzaile batekin bat badator, itzuli erabiltzailearen informazioa; bestela, itzuli None. Erabiltzaileen taularen eskema honako hau da:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite datu-basearen konexioa.
@param username Lortu beharreko erabiltzailearen erabiltzaile-izena.
@param password Lortu beharreko erabiltzailearen pasahitza.

@return Erabiltzailea aurkitzen bada, erabiltzailearen informazioa; bestela, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prestatutako adierazpena sortu
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Parametroak ezarri
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Adierazpena exekutatu
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Erabiltzailearen informazioa kopiatzen da
        }
    }

    // Baliogabeko adierazpenak askatu
    sqlite3_finalize(stmt);
    return userInfo; // NULL edo erabiltzailearen informazioa itzuli
}