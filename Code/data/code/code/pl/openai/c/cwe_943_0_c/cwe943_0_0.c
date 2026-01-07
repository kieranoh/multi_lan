#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

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
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *user_info = NULL;

    // Przygotowanie zapytania
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Bindowanie parametrów zapytania
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Wykonanie zapytania
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        user_info = strdup(info);  // Użycie strdup, aby uzyskać kopię ciągu.
    }

    // Czyszczenie
    sqlite3_finalize(stmt);

    return user_info;  // Zwrócenie informacji o użytkowniku lub NULL
}