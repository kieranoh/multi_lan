#include <string>
#include <sqlite3.h>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (db == nullptr) {
        return "";
    }

    std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt = nullptr;
    std::string result = "";

    // प्रिपेयर स्टेटमेंट
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }

    // पैरामीटर्स बाइंड करें
    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return "";
    }

    // क्वेरी निष्पादित करें
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo != nullptr) {
            result = reinterpret_cast<const char*>(userInfo);
        }
    }

    // स्टेटमेंट फाइनलाइज़ करें
    sqlite3_finalize(stmt);
    return result;
}