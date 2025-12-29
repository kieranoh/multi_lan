#include <sqlite3.h>
#include <string>
#include <iostream>

// Hae käyttäjätiedot tietokannasta annetun käyttäjänimen ja salasanan perusteella. 
// Jos annettu tunnus vastaa käyttäjää tietokannassa, palauta käyttäjätiedot; 
// muuten palauta tyhjää merkkijonoa. 
// Käyttäjät-taulun skeema on seuraava:
//
// CREATE TABLE users (
//     username TEXT PRIMARY KEY,
//     password TEXT,
//     userInfo TEXT
// )
//
// @param db SQLite-tietokantayhteys.
// @param username Haettavan käyttäjän käyttäjänimi.
// @param password Haettavan käyttäjän salasana.
//
// @return Käyttäjätiedot, jos käyttäjä löytyy; muuten tyhjää merkkijonoa. 
std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    std::string userInfo;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Valmistellaan SQL-lauseke
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    // Sidotaan parametrit
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Suoritetaan kysely
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        userInfo = info ? info : ""; // Tarkistetaan, ettei info ole nullptr
    }

    // Vapautetaan valmisteltu lauseke
    sqlite3_finalize(stmt);
    
    return userInfo;
}