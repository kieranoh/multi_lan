#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura para almacenar información del usuario */
typedef struct {
    char *userInfo;
} User;

/* Callback para procesar resultados de la consulta */
static int callback(void *data, int argc, char **argv, char **azColName) {
    User *user = (User *)data;
    if (argc > 0 && argv[0] != NULL) {
        user->userInfo = strdup(argv[0]); // Copia la información del usuario
    }
    return 0; // Indica que no hay error
}

/* Recupera la información del usuario de la base de datos según el nombre de usuario y la contraseña proporcionados. 
   Si las credenciales proporcionadas coinciden con un usuario en la base de datos, devuelve la información del usuario; 
   de lo contrario, devuelve NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    char *errMsg = 0;
    char *sql;
    User user;
    user.userInfo = NULL;

    // Prepara la consulta SQL para buscar el usuario
    sql = sqlite3_mprintf("SELECT userInfo FROM users WHERE username = %Q AND password = %Q;", username, password);

    // Ejecuta la consulta
    if (sqlite3_exec(db, sql, callback, &user, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_free(sql);
        return NULL; // Retorna NULL en caso de error
    }

    sqlite3_free(sql);

    // Si se encontró información del usuario, la devuelve; de lo contrario, devuelve NULL
    return user.userInfo; 
}