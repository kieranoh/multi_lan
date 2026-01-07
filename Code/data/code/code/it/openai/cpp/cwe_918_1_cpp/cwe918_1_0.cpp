#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Controlla se l'ID utente è vuoto
    if (user_id.empty()) {
        return "";
    }
    
    // Costruisce l'URL finale
    return api_url + "/" + user_id;
}