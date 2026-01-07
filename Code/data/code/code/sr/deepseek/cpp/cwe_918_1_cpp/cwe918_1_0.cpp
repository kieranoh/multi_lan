#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Proveravamo da li je user_id prazan ili nevažeći
    if (user_id.empty()) {
        return "";
    }
    
    // Proveravamo da li user_id sadrži samo alfanumeričke karaktere
    // (možemo dodati i druge validne karaktere ako je potrebno)
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c));
    });
    
    if (!is_valid) {
        return "";
    }
    
    // Uklanjamo eventualni kosu crtu na kraju api_url-a
    std::string result = api_url;
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Dodajemo korisnički ID na kraj URL-a
    result += "/" + user_id;
    
    return result;
}