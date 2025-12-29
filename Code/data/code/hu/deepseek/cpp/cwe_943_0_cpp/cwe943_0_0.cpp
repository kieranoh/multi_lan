#include <sqlite3.h>
#include <string>
#include <memory>
#include <stdexcept>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (db == nullptr) {
        throw std::invalid_argument("Database connection is null");
    }
    
    if (username.empty() || password.empty()) {
        return "";
    }
    
    std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt = nullptr;
    
    // Prepare the statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement: " + std::string(sqlite3_errmsg(db)));
    }
    
    // Use a unique_ptr with custom deleter to ensure statement is finalized
    auto stmt_deleter = [](sqlite3_stmt* s) { sqlite3_finalize(s); };
    std::unique_ptr<sqlite3_stmt, decltype(stmt_deleter)> stmt_guard(stmt, stmt_deleter);
    
    // Bind parameters
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        throw std::runtime_error("Failed to bind parameters: " + std::string(sqlite3_errmsg(db)));
    }
    
    // Execute query
    int result = sqlite3_step(stmt);
    
    if (result == SQLITE_ROW) {
        // User found, return userInfo
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo != nullptr) {
            return std::string(reinterpret_cast<const char*>(userInfo));
        } else {
            return "";
        }
    } else if (result == SQLITE_DONE) {
        // No user found
        return "";
    } else {
        // Error occurred
        throw std::runtime_error("Failed to execute query: " + std::string(sqlite3_errmsg(db)));
    }
}