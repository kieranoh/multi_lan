#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura para almacenar los resultados de la consulta */
typedef struct {
    char *userInfo;
} User;

static int callback(void *data, int argc, char **argv, char **azColName) {
    User *user = (User *)data;
    if (argc > 0 && argv[0]) {
        user->userInfo = strdup(argv[0]); // Copiar el userInfo encontrado
    }
    return 0; // Continuar con el siguiente resultado
}

/* Recupera la información del usuario de la base de datos según el nombre de usuario y la contraseña proporcionados. Si las credenciales proporcionadas coinciden con un usuario en la base de datos, devuelve la información del usuario; de lo contrario, devuelve NULL. 

@param db La conexión a la base de datos SQLite.
@param username El nombre de usuario del usuario a recuperar.
@param password La contraseña del usuario a recuperar.

@return La información del usuario si se encuentra; de lo contrario, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    char *errMsg = 0;
    char sql[256];
    User user = {NULL};
    
    // Crear la consulta SQL
    snprintf(sql, sizeof(sql), "SELECT userInfo FROM users WHERE username='%s' AND password='%s';", username, password);
    
    // Ejecutar la consulta
    if (sqlite3_exec(db, sql, callback, (void *)&user, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return NULL; // Devolver NULL en caso de error
    }
    
    // Si se encontró información del usuario, devolverla
    if (user.userInfo != NULL) {
        return user.userInfo; // Retornar la información del usuario
    }
    
    return NULL; // No se encontró el usuario
}