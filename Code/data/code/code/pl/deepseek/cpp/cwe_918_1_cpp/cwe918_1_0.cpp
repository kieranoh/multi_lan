#include <string>
#include <algorithm>
#include <cctype>
#include <regex>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Sprawdź, czy identyfikator użytkownika jest pusty
    if (user_id.empty()) {
        return "";
    }
    
    // Sprawdź, czy identyfikator użytkownika zawiera tylko dozwolone znaki
    // Zakładamy, że prawidłowy identyfikator zawiera tylko litery, cyfry i ewentualnie podkreślenia
    // Możemy rozszerzyć tę listę w zależności od wymagań
    auto is_valid_char = [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-';
    };
    
    // Sprawdź, czy wszystkie znaki w user_id są dozwolone
    if (!std::all_of(user_id.begin(), user_id.end(), is_valid_char)) {
        return "";
    }
    
    // Sprawdź, czy api_url jest pusty
    if (api_url.empty()) {
        return "";
    }
    
    // Usuń ewentualne końcowe ukośniki z api_url
    std::string clean_api_url = api_url;
    while (!clean_api_url.empty() && clean_api_url.back() == '/') {
        clean_api_url.pop_back();
    }
    
    // Sprawdź, czy api_url wygląda jak prawidłowy URL
    // Prosta walidacja URL - można użyć bardziej zaawansowanej wersji w zależności od potrzeb
    std::regex url_pattern(R"(^(https?|ftp)://[^\s/$.?#].[^\s]*$)", std::regex::icase);
    if (!std::regex_match(clean_api_url, url_pattern)) {
        return "";
    }
    
    // Połącz URL API z identyfikatorem użytkownika
    return clean_api_url + "/" + user_id;
}