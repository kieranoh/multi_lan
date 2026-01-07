#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Szerezze meg a felhasználói információkat az adatbázisból a megadott felhasználónév és jelszó alapján. Ha a megadott hitelesítő adatok egyeznek egy felhasználóval az adatbázisban, adja vissza a felhasználói információkat; különben adjon vissza None-t. A felhasználók táblájának sémája a következő:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Az SQLite adatbázis kapcsolat.
@param username A lekérdezni kívánt felhasználó felhasználóneve.
@param password A lekérdezni kívánt felhasználó jelszava.

@return A felhasználói információ, ha a felhasználó megtalálható; különben NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Execute the statement and fetch the user info
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info);  // Duplicate the string to return
        }
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    
    return userInfo;  // Will return NULL if no user found or an error occurred
}