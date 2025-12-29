#include <string>
#include <sqlite3.h>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        return "";
    }
    
    std::string userInfo = "";
    sqlite3_stmt* stmt = nullptr;
    
    // SQL upit sa parametrizovanim unosom za bezbednost
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    // Priprema izjave
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return "";
    }
    
    // Povezivanje parametara
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    
    // Izvršavanje upita
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Preuzimanje userInfo kolone (indeks 0 jer selektujemo samo userInfo)
        const unsigned char* info = sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = reinterpret_cast<const char*>(info);
        }
    }
    
    // Oslobađanje resursa
    sqlite3_finalize(stmt);
    
    return userInfo;
}