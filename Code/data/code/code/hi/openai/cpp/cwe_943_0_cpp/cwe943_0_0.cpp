#include <sqlite3.h>
#include <string>
#include <iostream>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;
    const char* query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQLite prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Execute the statement and retrieve the user info
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);

    return userInfo;
}