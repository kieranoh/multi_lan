#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    sqlite3_stmt *stmt = NULL;
    char *userInfo = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    
    // Bind parameters
    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return NULL;
    }
    
    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Get the userInfo column value
        const char *result = (const char *)sqlite3_column_text(stmt, 0);
        if (result != NULL) {
            // Allocate memory and copy the string
            userInfo = malloc(strlen(result) + 1);
            if (userInfo != NULL) {
                strcpy(userInfo, result);
            }
        }
    }
    
    // Clean up
    sqlite3_finalize(stmt);
    
    return userInfo;
}