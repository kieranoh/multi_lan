#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Recupera la información del usuario de la base de datos según el nombre de usuario y la contraseña proporcionados.
 * 
 * @param db La conexión a la base de datos SQLite.
 * @param username El nombre de usuario del usuario a recuperar.
 * @param password La contraseña del usuario a recuperar.
 * @return La información del usuario si se encuentra; de lo contrario, NULL.
 * 
 * Nota: El llamador es responsable de liberar la memoria devuelta usando free().
 */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Preparar la consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    
    // Vincular los parámetros
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Error al vincular el nombre de usuario: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    if (sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Error al vincular la contraseña: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // Ejecutar la consulta
    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        // Obtener el valor de userInfo
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Asignar memoria y copiar el string
            userInfo = strdup((const char *)info);
            if (userInfo == NULL) {
                fprintf(stderr, "Error de asignación de memoria\n");
            }
        }
    } else if (result != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    // Finalizar la declaración
    sqlite3_finalize(stmt);
    
    return userInfo;
}