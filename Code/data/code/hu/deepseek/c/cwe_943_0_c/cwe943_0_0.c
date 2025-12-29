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
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    if (sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo != NULL) {
            result = strdup((const char*)userInfo);
        }
    }
    
    sqlite3_finalize(stmt);
    return result;
}