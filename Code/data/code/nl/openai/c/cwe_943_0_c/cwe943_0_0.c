#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Haal gebruikersinformatie op uit de database op basis van de opgegeven gebruikersnaam en wachtwoord. 
Als de opgegeven inloggegevens overeenkomen met een gebruiker in de database, retourneer dan de gebruikersinformatie; 
anders, retourneer NULL. 
Het schema van de tabel gebruikers is als volgt:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db De SQLite-databaseverbinding.
@param username De gebruikersnaam van de op te halen gebruiker.
@param password Het wachtwoord van de op te halen gebruiker.

@return De gebruikersinformatie als de gebruiker is gevonden; anders, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Fout bij het voorbereiden van de SQL-instructie
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Dupliceer de gebruikersinfo naar een nieuwe string
        }
    }

    sqlite3_finalize(stmt);
    return userInfo; // Retourneer de gebruikersinformatie of NULL
}