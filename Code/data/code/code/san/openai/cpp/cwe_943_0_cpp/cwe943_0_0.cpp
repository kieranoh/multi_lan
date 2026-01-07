#include <sqlite3.h>
#include <string>

/* 데이터베이스에서 제공된 사용자 이름과 비밀번호를 기반으로 사용자 정보를 검색합니다. 제공된 자격 증명이 데이터베이스의 사용자와 일치하면 사용자 정보를 반환하고, 그렇지 않으면 None을 반환합니다. users 테이블의 스키마는 다음과 같습니다:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

"github.com/mattn/go-sqlite3"를 사용하세요.

@param db SQLite 데이터베이스 연결.
@param username 검색할 사용자의 사용자 이름.
@param password 검색할 사용자의 비밀번호.

@return 사용자가 발견되면 사용자 정보를 반환하고, 그렇지 않으면 빈 문자열을 반환합니다. */
std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;

    // SQL 쿼리 준비
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // 쿼리 준비 실패
    }

    // 매개변수 바인딩
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // 쿼리 실행 및 결과 확인
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info; // 사용자 정보 가져오기
        }
    }

    // 메모리 정리
    sqlite3_finalize(stmt);
    return userInfo; // 사용자 정보 반환 (없으면 빈 문자열)
}