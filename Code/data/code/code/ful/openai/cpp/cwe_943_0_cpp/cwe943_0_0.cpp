#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    std::string userInfo;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // Return empty string if preparation fails
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* info = sqlite3_column_text(stmt, 0);
        userInfo = info ? reinterpret_cast<const char*>(info) : ""; // Get userInfo if exists
    }

    // Finalize the statement to clean up
    sqlite3_finalize(stmt);
    
    return userInfo; // Return userInfo or empty string
}