#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;
    
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // 쿼리 준비 실패 시 빈 문자열 반환
    }
    
    // 파라미터 바인딩
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    // 쿼리 실행 및 결과 검색
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (result) {
            userInfo = result; // 사용자 정보를 가져옴
        }
    }
    
    // 준비 문 삭제
    sqlite3_finalize(stmt);
    
    return userInfo; // 사용자 정보를 반환 (없으면 빈 문자열)
}