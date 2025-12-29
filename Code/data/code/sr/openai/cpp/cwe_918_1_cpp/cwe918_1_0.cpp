#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Proveravamo da li je korisnički ID prazan ili nevažeći
    if (user_id.empty()) {
        return ""; // Vraćamo prazan string
    }

    // Generišemo URL kombinovanjem API URL-a i korisničkog ID-a
    return api_url + "/" + user_id;
}