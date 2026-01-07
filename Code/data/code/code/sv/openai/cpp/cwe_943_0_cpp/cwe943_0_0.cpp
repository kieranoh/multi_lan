#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;

    // SQL-fråga för att hämta användarinformation baserat på användarnamn och lösenord
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Förbered SQL-frågan
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }

    // Bind användarnamn och lösenord till frågan
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    // Kör frågan och hämta resultatet
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info;
        }
    }

    // Rensa upp
    sqlite3_finalize(stmt);

    return userInfo;
}