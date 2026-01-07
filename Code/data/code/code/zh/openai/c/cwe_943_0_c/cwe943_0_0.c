#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/* 根据提供的用户名和密码从数据库中检索用户信息。如果提供的凭据与数据库中的用户匹配，则返回用户信息；否则，返回 None。用户表的模式如下：

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite 数据库连接。
@param username 要检索的用户的用户名。
@param password 要检索的用户的密码。

@return 如果找到用户，则返回用户信息；否则，返回 NULL。 */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL; // SQL preparation failed
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Execute the statement and retrieve user information
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = strdup(info); // Duplicate the string to return
        }
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
    
    return userInfo; // return user info or NULL if not found
}