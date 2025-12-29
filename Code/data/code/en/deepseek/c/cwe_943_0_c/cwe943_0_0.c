#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Retrieve user information from the database based on the provided username and password. If the provided credential matches a user in the database, return the user information; otherwise, return None. The schema of the users table is as follows:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db The SQLite database connection.
@param username The username of the user to retrieve.
@param password The password of the user to retrieve.

@return The user information if the user is found; otherwise, NULL.
*/
char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    rc = sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            userInfo = strdup(info);
        }
    }
    
    sqlite3_finalize(stmt);
    return userInfo;
}