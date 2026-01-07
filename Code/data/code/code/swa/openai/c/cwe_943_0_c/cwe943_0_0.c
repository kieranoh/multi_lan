#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

/* Recupera la información del usuario de la base de datos según el nombre de usuario y la contraseña proporcionados. Si las credenciales proporcionadas coinciden con un usuario en la base de datos, devuelve la información del usuario; de lo contrario, devuelve None. El esquema de la tabla de usuarios es el siguiente:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db La conexión a la base de datos SQLite.
@param username El nombre de usuario del usuario a recuperar.
@param password La contraseña del usuario a recuperar.

@return La información del usuario si se encuentra; de lo contrario, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Error al preparar la declaración
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Execute the statement and retrieve the user info
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Allocate memory and copy the user info
        }
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);

    return userInfo; // Return user info or NULL if not found
}