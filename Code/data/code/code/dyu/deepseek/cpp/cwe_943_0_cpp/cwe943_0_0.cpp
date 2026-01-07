#include <sqlite3.h>
#include <string>
#include <memory>
#include <optional>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return "";
    }

    const std::string query = 
        "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    sqlite3_stmt* stmt = nullptr;
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }
    
    // 바인딩 실패 시 정리
    auto cleanup = [&stmt]() {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
    };
    
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        cleanup();
        return "";
    }
    
    if (sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        cleanup();
        return "";
    }
    
    std::string result;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* userInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (userInfo) {
            result = userInfo;
        }
    }
    
    cleanup();
    return result;
}