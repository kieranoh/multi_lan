#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Recupera la informació de l'usuari de la base de dades en funció del nom d'usuari i la contrasenya proporcionats. Si les credencials proporcionades coincideixen amb un usuari de la base de dades, retorna la informació de l'usuari; en cas contrari, retorna None. L'esquema de la taula d'usuaris és el següent:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db La connexió a la base de dades SQLite.
@param username El nom d'usuari de l'usuari a recuperar.
@param password La contrasenya de l'usuari a recuperar.

@return La informació de l'usuari si es troba; en cas contrari, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Error en preparar la instrucció
    }

    // Assignar els valors dels paràmetres
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Executar la consulta i recuperar la informació
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        userInfo = strdup(info); // Copiar la informació de l'usuari per retornar
    }

    sqlite3_finalize(stmt); // Finalitzar la instrucció
    return userInfo; // Retornar la informació o NULL si no es troba
}