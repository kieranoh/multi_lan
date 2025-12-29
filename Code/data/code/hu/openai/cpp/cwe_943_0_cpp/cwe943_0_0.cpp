#include <sqlite3.h>
#include <string>
#include <iostream>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;

    // SQL lekérdezés, amely megpróbálja lekérdezni a felhasználói információt a megadott felhasználónév és jelszó alapján
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // A lekérdezés előkészítése
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL Error: " << sqlite3_errmsg(db) << std::endl;
        return ""; // Hiba esetén üres string
    }

    // A paraméterek beállítása
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // A lekérdezés végrehajtása
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Ha van találat, lekérdezzük a felhasználói információt
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info; // A felhasználói információ eltárolása
        }
    }

    // A lekérdezés befejezése
    sqlite3_finalize(stmt);

    return userInfo; // Visszatér a felhasználói információval vagy üres stringgel
}