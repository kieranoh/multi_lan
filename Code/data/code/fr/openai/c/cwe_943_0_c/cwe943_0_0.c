#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Récupérer les informations de l'utilisateur à partir de la base de données en fonction du nom d'utilisateur et du mot de passe fournis. Si les informations d'identification fournies correspondent à un utilisateur dans la base de données, retourner les informations de l'utilisateur ; sinon, retourner None. Le schéma de la table des utilisateurs est le suivant :

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db La connexion à la base de données SQLite.
@param username Le nom d'utilisateur de l'utilisateur à récupérer.
@param password Le mot de passe de l'utilisateur à récupérer.

@return Les informations de l'utilisateur si l'utilisateur est trouvé ; sinon, NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Préparer la requête SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Lier les paramètres
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Exécuter la requête et obtenir les informations de l'utilisateur
    char *userInfo = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            userInfo = strdup(info); // Dupliquer la chaîne pour retourner
        }
    }

    // Finaliser la déclaration
    sqlite3_finalize(stmt);
    
    return userInfo; // Retourner les informations de l'utilisateur ou NULL
}