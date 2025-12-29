#include <sqlite3.h>
#include <string>
#include <iostream>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;

    // SQL galdera prestatzea
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return ""; // Huts itzultzea errorea gertatzen bada
    }

    // Parametroak lotzea
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Galdera exekutatzea
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info; // Erabiltzailearen informazioa jasotzea
        }
    }

    // Biñoa askatzea
    sqlite3_finalize(stmt);

    return userInfo; // Erabiltzailea aurkitu bada, informazioa itzultzea; bestela, string huts bat.
}