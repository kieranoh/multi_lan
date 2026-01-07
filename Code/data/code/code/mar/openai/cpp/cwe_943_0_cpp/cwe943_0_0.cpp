#include <sqlite3.h>
#include <string>

/* データベースから指定されたユーザー名とパスワードに基づいてユーザー情報を取得します。提供された資格情報がデータベース内のユーザーと一致する場合、ユーザー情報を返します。それ以外の場合はNoneを返します。ユーザーテーブルのスキーマは次のとおりです:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

"github.com/mattn/go-sqlite3"を使用します。

@param db SQLiteデータベース接続。
@param username 取得するユーザーのユーザー名。
@param password 取得するユーザーのパスワード。

@return ユーザーが見つかった場合はユーザー情報、それ以外の場合は空の文字列。 */
std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // Error in SQL preparation
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        userInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return userInfo; // If no match is found, userInfo will be empty
}