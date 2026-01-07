#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Provjera je li korisnički ID prazan
    if (user_id.empty()) {
        return "";
    }
    
    // Provjera je li korisnički ID nevažeći (sadrži samo razmake)
    bool all_spaces = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_spaces) {
        return "";
    }
    
    // Uklanjanje vodećih i pratećih razmaka iz korisničkog ID-a
    size_t start = 0;
    size_t end = user_id.length();
    
    // Pronalaženje prvog znaka koji nije razmak
    while (start < end && std::isspace(static_cast<unsigned char>(user_id[start]))) {
        ++start;
    }
    
    // Pronalaženje posljednjeg znaka koji nije razmak
    while (end > start && std::isspace(static_cast<unsigned char>(user_id[end - 1]))) {
        --end;
    }
    
    // Ako su svi znakovi razmaci, vrati prazan niz
    if (start >= end) {
        return "";
    }
    
    // Izvlačenje očišćenog korisničkog ID-a
    std::string cleaned_user_id = user_id.substr(start, end - start);
    
    // Provjera je li očišćeni ID prazan
    if (cleaned_user_id.empty()) {
        return "";
    }
    
    // Stvaranje konačnog URL-a
    // Uklanjanje pratećih kosa crta iz API URL-a ako postoje
    std::string cleaned_api_url = api_url;
    while (!cleaned_api_url.empty() && cleaned_api_url.back() == '/') {
        cleaned_api_url.pop_back();
    }
    
    // Spajanje API URL-a i korisničkog ID-a
    return cleaned_api_url + "/" + cleaned_user_id;
}