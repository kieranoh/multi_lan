#include <string>
#include <sqlite3.h>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string result;
    sqlite3_stmt* stmt = nullptr;
    
    const std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return result; // Return empty string on preparation error
    }
    
    // Bind parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Get the userInfo column value
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo != nullptr) {
            result = reinterpret_cast<const char*>(userInfo);
        }
    }
    
    // Clean up
    sqlite3_finalize(stmt);
    
    return result;
}