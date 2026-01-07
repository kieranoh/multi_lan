#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    const char* query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // Error in preparing statement
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Execute the query and retrieve the user info
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* info = sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = reinterpret_cast<const char*>(info);
        }
    }

    // Clean up
    sqlite3_finalize(stmt);

    return userInfo; // Return user info or empty string if not found
}