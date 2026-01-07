#include <sqlite3.h>
#include <string>
#include <optional>

std::optional<std::string> getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return std::nullopt;
    }

    const std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    std::optional<std::string> result = std::nullopt;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo) {
            result = std::string(reinterpret_cast<const char*>(userInfo));
        }
    }

    sqlite3_finalize(stmt);
    return result;
}