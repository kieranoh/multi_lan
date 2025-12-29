#include <sqlite3.h>
#include <string>
#include <optional>

std::optional<std::string> getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return std::nullopt;
    }

    const char* query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt = nullptr;

    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return std::nullopt;
    }

    std::optional<std::string> result = std::nullopt;

    // 执行查询
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* userInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (userInfo) {
            result = std::string(userInfo);
        }
    }

    // 清理语句
    sqlite3_finalize(stmt);
    return result;
}