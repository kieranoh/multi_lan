#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;

    // SQL 쿼리 준비: 사용자 이름과 비밀번호를 기반으로 사용자 정보를 검색
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // 쿼리 준비 실패
    }

    // 바인딩 변수 설정
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // 쿼리 실행 및 결과 수집
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // 사용자 정보가 발견되면 가져오기
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info;
        }
    }

    // 자원 해제
    sqlite3_finalize(stmt);

    return userInfo; // 사용자 정보 반환 (없으면 빈 문자열)
}