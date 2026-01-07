#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

/* 제공된 사용자 이름과 비밀번호를 기반으로 데이터베이스에서 사용자 정보를 검색합니다. 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고, 그렇지 않으면 None을 반환합니다. users 테이블의 스키마는 다음과 같습니다:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db SQLite 데이터베이스 연결.
@param username 검색할 사용자의 사용자 이름.
@param password 검색할 사용자의 비밀번호.

@return 사용자가 발견되면 사용자 정보; 그렇지 않으면 NULL. */
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    char *userInfo = NULL;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Execute the query and check for results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        userInfo = malloc(strlen(info) + 1);
        if (userInfo != NULL) {
            strcpy(userInfo, info);
        }
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return userInfo;
}