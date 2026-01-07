#include <string>
#include <sqlite3.h>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string result = "";
    
    if (!db) {
        return result;
    }
    
    sqlite3_stmt* stmt = nullptr;
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return result;
    }
    
    // Bind parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // User found, get the userInfo
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo) {
            result = reinterpret_cast<const char*>(userInfo);
        }
    }
    
    // Clean up
    sqlite3_finalize(stmt);
    
    return result;
}