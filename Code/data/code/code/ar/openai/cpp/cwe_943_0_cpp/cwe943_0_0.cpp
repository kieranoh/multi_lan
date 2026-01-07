#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;

    // إعداد الاستعلام
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // معالجة الأخطاء
    }

    // ربط المتغيرات
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // تنفيذ الاستعلام
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info; // استرجاع معلومات المستخدم
        }
    }

    // إنهاء الاستعلام
    sqlite3_finalize(stmt);
    return userInfo; // إرجاع معلومات المستخدم أو سلسلة فارغة
}