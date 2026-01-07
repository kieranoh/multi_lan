#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // 쿼리 준비 실패 시 빈 문자열 반환
    }
    
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info; // 사용자 정보를 가져옴
        }
    }
    
    sqlite3_finalize(stmt); // 메모리 해제
    return userInfo; // 사용자 정보 반환 (발견되지 않으면 빈 문자열)
}