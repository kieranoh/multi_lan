#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // Return empty string on error
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    std::string userInfo;

    // Execute the statement and fetch the results
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        userInfo = (info != nullptr) ? info : ""; // Retrieve userInfo if available
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return userInfo; // Return userInfo or empty string if not found
}