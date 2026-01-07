#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;
    
    // Prepare the SQL statement to search for the user
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        // Handle error in preparing statement
        return "";
    }
    
    // Bind the username and password parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    // Execute the statement and retrieve user information
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* info = sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = reinterpret_cast<const char*>(info);
        }
    }
    
    // Finalize the statement to release resources
    sqlite3_finalize(stmt);
    
    // Return the user information or an empty string if not found
    return userInfo;
}