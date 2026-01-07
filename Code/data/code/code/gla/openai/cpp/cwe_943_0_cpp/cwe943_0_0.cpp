#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;

    // SQLクエリを準備
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // エラーが発生した場合は空の文字列を返す
    }

    // プレースホルダに値をバインド
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // クエリを実行
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    // ステートメントを解放
    sqlite3_finalize(stmt);

    return userInfo; // ユーザー情報を返す（見つからなければ空文字列）
}