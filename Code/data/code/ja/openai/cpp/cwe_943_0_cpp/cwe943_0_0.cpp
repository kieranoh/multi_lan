#include <sqlite3.h>
#include <string>
#include <iostream>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;

    // SQLクエリを準備
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    // プレースホルダに値をバインド
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // クエリを実行
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (result != nullptr) {
            userInfo = result; // ユーザー情報を取得
        }
    }

    // ステートメントを解放
    sqlite3_finalize(stmt);

    return userInfo; // ユーザー情報を返す（見つからなければ空文字列）
}