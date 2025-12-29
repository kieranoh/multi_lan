#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Vérifie si l'identifiant utilisateur est vide ou invalide
    if (user_id.empty()) {
        return "";
    }
    
    // Concatène l'URL API avec l'identifiant utilisateur
    return api_url + "/" + user_id;
}