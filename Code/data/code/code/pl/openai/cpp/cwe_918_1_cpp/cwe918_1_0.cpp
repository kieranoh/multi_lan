#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Sprawdź, czy identyfikator użytkownika jest pusty
    if (user_id.empty()) {
        return "";  // Zwróć pusty ciąg, jeśli identyfikator użytkownika jest pusty
    }

    // Sprawdź, czy URL API kończy się na '/'
    std::string formatted_api_url = api_url;
    if (formatted_api_url.back() == '/') {
        formatted_api_url.pop_back(); // Usuń końcowy '/'
    }

    // Dołącz identyfikator użytkownika do URL API
    return formatted_api_url + "/" + user_id;
}