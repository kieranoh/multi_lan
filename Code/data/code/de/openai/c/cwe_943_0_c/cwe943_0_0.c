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
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Fehler bei der Vorbereitung der Abfrage
    }
    
    // Bind the parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // Execute the statement and retrieve the userInfo
    char *userInfo = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Kopiere die Benutzerinformationen
        }
    }
    
    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
    
    return userInfo; // Gibt NULL zurück, wenn kein Benutzer gefunden wurde
}