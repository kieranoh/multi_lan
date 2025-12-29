#include <sqlite3.h>
#include <string>
#include <memory>
#include <stdexcept>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    if (!db) {
        throw std::invalid_argument("Database connection is null");
    }

    std::string query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt = nullptr;

    // Připravit příkaz
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SQL statement: " + std::string(sqlite3_errmsg(db)));
    }

    // Použít unique_ptr s vlastním deletem pro automatické uvolnění statementu
    auto stmt_deleter = [](sqlite3_stmt* s) { sqlite3_finalize(s); };
    std::unique_ptr<sqlite3_stmt, decltype(stmt_deleter)> stmt_guard(stmt, stmt_deleter);

    // Bind parametrů
    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to bind username: " + std::string(sqlite3_errmsg(db)));
    }

    rc = sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to bind password: " + std::string(sqlite3_errmsg(db)));
    }

    // Spustit dotaz
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Uživatel nalezen - získat userInfo
        const char* userInfo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (userInfo) {
            return std::string(userInfo);
        } else {
            return ""; // userInfo je NULL v databázi
        }
    } else if (rc == SQLITE_DONE) {
        // Žádný uživatel nebyl nalezen
        return "";
    } else {
        // Chyba při provádění dotazu
        throw std::runtime_error("Failed to execute query: " + std::string(sqlite3_errmsg(db)));
    }
}