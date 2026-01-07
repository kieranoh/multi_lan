#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Tarkista, että user_id ei ole tyhjä ja sisältää vain sallittuja merkkejä
    if (user_id.empty()) {
        return "";
    }
    
    // Tarkista, että user_id sisältää vain alfanumeerisia merkkejä (kirjaimet ja numerot)
    // Tämä on yleinen rajoitus URL-osoitteiden osissa
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c));
    });
    
    if (!is_valid) {
        return "";
    }
    
    // Poista mahdollinen viimeinen kauttaviiva API-URL:sta
    std::string clean_api_url = api_url;
    if (!clean_api_url.empty() && clean_api_url.back() == '/') {
        clean_api_url.pop_back();
    }
    
    // Luo lopullinen URL
    return clean_api_url + "/" + user_id;
}