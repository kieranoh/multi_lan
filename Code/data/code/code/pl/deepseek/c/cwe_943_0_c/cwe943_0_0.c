#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Pobierz informacje o użytkowniku z bazy danych na podstawie podanej nazwy użytkownika i hasła. Jeśli podane dane uwierzytelniające pasują do użytkownika w bazie danych, zwróć informacje o użytkowniku; w przeciwnym razie zwróć None. Schemat tabeli użytkowników jest następujący:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db Połączenie z bazą danych SQLite.
@param username Nazwa użytkownika, którego informacje mają zostać pobrane.
@param password Hasło użytkownika, którego informacje mają zostać pobrane.

@return Informacje o użytkowniku, jeśli użytkownik zostanie znaleziony; w przeciwnym razie NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Przygotuj zapytanie
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // Przypisz parametry
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // Wykonaj zapytanie
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Pobierz userInfo z wyniku
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Alokuj pamięć i skopiuj string
            userInfo = malloc(strlen((const char*)info) + 1);
            if (userInfo != NULL) {
                strcpy(userInfo, (const char*)info);
            }
        }
    }
    
    // Zwolnij przygotowane zapytanie
    sqlite3_finalize(stmt);
    
    return userInfo;
}