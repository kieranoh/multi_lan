#include <string>
#include <sqlite3.h>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return "";
    }
    
    std::string result = "";
    sqlite3_stmt* stmt = nullptr;
    
    // Pripremi SQL upit s parametrima
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return "";
    }
    
    // Poveži parametre
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    // Izvrši upit
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Dohvati userInfo iz rezultata
        const unsigned char* userInfo = sqlite3_column_text(stmt, 0);
        if (userInfo) {
            result = reinterpret_cast<const char*>(userInfo);
        }
    }
    
    // Oslobodi pripremljenu izjavu
    sqlite3_finalize(stmt);
    
    return result;
}