#include <sqlite3.h>
#include <string>
#include <iostream>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return ""; // Vrátí prázdný řetězec v případě chyby
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        userInfo = result ? result : ""; // Ujistit se, že výsledek není nullptr
    }

    sqlite3_finalize(stmt);
    return userInfo; // Vrátí informace o uživateli nebo prázdný řetězec, pokud není nalezen
}