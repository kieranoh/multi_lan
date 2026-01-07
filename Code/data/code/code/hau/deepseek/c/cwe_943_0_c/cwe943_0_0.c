#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt = NULL;
    char *result = NULL;
    
    // Prepare SQL statement with parameterized query to prevent SQL injection
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        // Failed to prepare statement
        return NULL;
    }
    
    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    // Execute query
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // User found, retrieve userInfo
        const char *userInfo = (const char *)sqlite3_column_text(stmt, 0);
        
        if (userInfo != NULL) {
            // Allocate memory for result and copy the string
            result = malloc(strlen(userInfo) + 1);
            if (result != NULL) {
                strcpy(result, userInfo);
            }
        }
    }
    
    // Clean up
    sqlite3_finalize(stmt);
    
    return result;
}