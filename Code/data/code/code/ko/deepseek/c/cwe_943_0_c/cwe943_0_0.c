#include <sqlite3.h>
#include <stdio.h>
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
    if (db == NULL || username == NULL || password == NULL) {
        return NULL;
    }

    sqlite3_stmt *stmt = NULL;
    char *user_info = NULL;
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";

    // SQL 문 준비
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }

    // 매개변수 바인딩
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // 쿼리 실행
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // userInfo 열의 데이터 가져오기
        const unsigned char *info = sqlite3_column_text(stmt, 0);
        if (info != NULL) {
            // 메모리 할당 및 문자열 복사
            size_t len = strlen((const char *)info);
            user_info = (char *)malloc(len + 1);
            if (user_info != NULL) {
                strcpy(user_info, (const char *)info);
            }
        }
    }

    // 명령문 정리
    sqlite3_finalize(stmt);
    return user_info;
}