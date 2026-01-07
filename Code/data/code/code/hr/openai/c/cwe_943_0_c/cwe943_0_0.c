#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Preuzmite informacije o korisniku iz baze podataka na temelju zadanog korisničkog imena i lozinke. Ako zadata vjerodajnica odgovara korisniku u bazi podataka, vratite informacije o korisniku; inače, vratite None. Shema tablice korisnika je sljedeća:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Veza na SQLite bazu podataka.
@param username Korisničko ime korisnika koji se preuzima.
@param password Lozinka korisnika koji se preuzima.

@return Informacije o korisniku ako je korisnik pronađen; inače, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Pripremite SQL upit
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Neuspjela priprema
    }

    // Bind korisničkog imena i lozinke
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Izvršite upit i preuzmite rezultate
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Kopirajte informacije o korisniku
        }
    }

    // Očistite resurse
    sqlite3_finalize(stmt);

    return userInfo; // Vratite informacije o korisniku ili NULL
}