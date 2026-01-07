#include <sqlite3.h>
#include <string>
#include <memory>
#include <stdexcept>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return "";
    }

    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt = nullptr;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }

    // Bind parameters
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return "";
    }

    std::string result;

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo) {
            result = reinterpret_cast<const char*>(userInfo);
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    return result;
}