#include <sqlite3.h>
#include <string>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;

    // Préparer la requête SQL pour sélectionner les informations de l'utilisateur
    const char* query = "SELECT userInfo FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        return ""; // Erreur dans la préparation de la requête
    }

    // Lier les paramètres de la requête
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Exécuter la requête et récupérer les résultats
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Si un utilisateur est trouvé, récupérer les informations
        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (info) {
            userInfo = info; // Stocker les informations de l'utilisateur
        }
    }

    // Finaliser la déclaration
    sqlite3_finalize(stmt);

    return userInfo; // Retourner les informations de l'utilisateur ou une chaîne vide
}