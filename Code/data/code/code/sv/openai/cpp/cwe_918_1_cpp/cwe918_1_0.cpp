#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Kontrollera om användar-ID:t är tomt eller ogiltigt
    if (user_id.empty()) {
        return "";
    }
    
    // Skapa den fullständiga URL:en
    return api_url + "/" + user_id;
}