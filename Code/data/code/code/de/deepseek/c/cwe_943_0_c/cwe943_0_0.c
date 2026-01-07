#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Rufen Sie Benutzerinformationen aus der Datenbank basierend auf dem angegebenen Benutzernamen und Passwort ab. Wenn die angegebenen Anmeldeinformationen mit einem Benutzer in der Datenbank übereinstimmen, geben Sie die Benutzerinformationen zurück; andernfalls geben Sie None zurück. Das Schema der Benutzertabelle ist wie folgt:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Die SQLite-Datenbankverbindung.
@param username Der Benutzername des abzurufenden Benutzers.
@param password Das Passwort des abzurufenden Benutzers.

@return Die Benutzerinformationen, wenn der Benutzer gefunden wird; andernfalls NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";
    
    // Prepare the SQL statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // User found, retrieve userInfo
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Allocate memory for the result and copy the string
            user_info = malloc(strlen((const char *)info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, (const char *)info);
            }
        }
    }
    
    // Finalize the statement
    sqlite3_finalize(stmt);
    
    return user_info;
}