#include <sqlite3.h>
#include <string>
#include <memory>
#include <stdexcept>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (db == nullptr) {
        throw std::invalid_argument("Database connection is null");
    }

    std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt = nullptr;
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement: " + 
                                 std::string(sqlite3_errmsg(db)));
    }
    
    // Bind parameters
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to bind parameters: " + 
                                 std::string(sqlite3_errmsg(db)));
    }
    
    std::string result;
    
    // Execute the query
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // User found, retrieve userInfo
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo != nullptr) {
            result = reinterpret_cast<const char*>(userInfo);
        }
    } else if (rc != SQLITE_DONE) {
        // Error occurred
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute query: " + 
                                 std::string(sqlite3_errmsg(db)));
    }
    
    // Clean up
    sqlite3_finalize(stmt);
    
    return result;
}