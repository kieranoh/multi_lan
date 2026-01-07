#include <sqlite3.h>
#include <stdio.h>
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
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    // Vincular parámetros
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // Ejecutar la consulta
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Obtener el valor de userInfo
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Asignar memoria para copiar la cadena
            user_info = malloc(strlen((const char *)info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, (const char *)info);
            }
        }
    }
    
    // Finalizar la declaración
    sqlite3_finalize(stmt);
    
    return user_info;
}