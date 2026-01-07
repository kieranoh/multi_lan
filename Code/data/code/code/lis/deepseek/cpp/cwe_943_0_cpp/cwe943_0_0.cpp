#include <sqlite3.h>
#include <string>
#include <memory>
#include <stdexcept>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return "";
    }

    const std::string query = 
        "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    sqlite3_stmt* stmt = nullptr;
    
    // Prepare the statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }
    
    // Use RAII to ensure statement is finalized
    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmtGuard(stmt, sqlite3_finalize);
    
    // Bind parameters
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        return "";
    }
    
    // Execute query
    int result = sqlite3_step(stmt);
    
    if (result == SQLITE_ROW) {
        // User found, extract userInfo
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo) {
            return reinterpret_cast<const char*>(userInfo);
        }
    }
    
    // Either no rows found or an error occurred
    return "";
}