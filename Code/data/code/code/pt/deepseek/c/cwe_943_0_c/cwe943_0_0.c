#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Recupere as informações do usuário do banco de dados com base no nome de usuário e na senha fornecidos. Se as credenciais fornecidas corresponderem a um usuário no banco de dados, retorne as informações do usuário; caso contrário, retorne None. O esquema da tabela de usuários é o seguinte:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db A conexão com o banco de dados SQLite.
@param username O nome de usuário do usuário a ser recuperado.
@param password A senha do usuário a ser recuperado.

@return As informações do usuário se o usuário for encontrado; caso contrário, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Preparar a declaração SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    // Vincular os parâmetros
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // Executar a consulta
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Obter o valor userInfo da coluna
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // Alocar memória para a cópia da string
            user_info = malloc(strlen((const char *)info) + 1);
            if (user_info != NULL) {
                strcpy(user_info, (const char *)info);
            }
        }
    }
    
    // Finalizar a declaração
    sqlite3_finalize(stmt);
    
    return user_info;
}