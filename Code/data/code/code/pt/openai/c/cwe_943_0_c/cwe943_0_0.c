#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

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
    sqlite3_stmt *stmt;
    const char *query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepara a consulta SQL
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // Falha ao preparar a consulta
    }

    // Vincula os parâmetros
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Executa a consulta e verifica se encontramos um usuário
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        userInfo = strdup(info); // Duplicar a string de informações do usuário
    }

    // Finaliza a instrução e libera recursos
    sqlite3_finalize(stmt);
    
    return userInfo; // Retorna as informações do usuário ou NULL se não encontrado
}