#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Tarkistetaan, että käyttäjä-ID ei ole tyhjää
    if (user_id.empty()) {
        return "";  // Palautetaan tyhjää merkkijonoa, jos käyttäjä-ID on tyhjää
    }
    
    // Liitetään käyttäjä-ID API-URL:iin
    return api_url + "/" + user_id;
}