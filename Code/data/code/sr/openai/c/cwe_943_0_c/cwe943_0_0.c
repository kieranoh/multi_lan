#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Preuzmite informacije o korisniku iz baze podataka na osnovu datog korisničkog imena i lozinke. Ako se dati podaci poklapaju sa korisnikom u bazi, vratite informacije o korisniku; u suprotnom, vratite None. Šema tabele korisnika je sledeća:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Veza sa SQLite bazom podataka.
@param username Korisničko ime korisnika koji se preuzima.
@param password Lozinka korisnika koji se preuzima.

@return Informacije o korisniku ako je korisnik pronađen; u suprotnom, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Priprema SQL upita
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // Bind korisničkog imena i lozinke
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Izvršavanje upita i dobijanje rezultata
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Kopiraj informacije o korisniku
        }
    }

    // Oslobađanje resursa
    sqlite3_finalize(stmt);
    
    return userInfo; // Vraća informacije o korisniku ili NULL
}