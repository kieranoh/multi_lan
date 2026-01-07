#include <sqlite3.h>
#include <string>
#include <memory>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return "";
    }
    
    std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt = nullptr;
    
    // Prestatu kontsulta
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }
    
    // Lotu parametroak
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return "";
    }
    
    std::string userInfo;
    
    // Exekutatu kontsulta
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* result = sqlite3_column_text(stmt, 0);
        if (result) {
            userInfo = reinterpret_cast<const char*>(result);
        }
    }
    
    // Askatu adierazpena
    sqlite3_finalize(stmt);
    
    return userInfo;
}