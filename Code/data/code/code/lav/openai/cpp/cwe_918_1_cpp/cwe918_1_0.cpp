#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Pārbaudām, vai lietotāja ID ir tukšs
    if (user_id.empty()) {
        return ""; // Atgriežam tukšu virkni, ja ID nav derīgs
    }
    // Veidojam un atgriežam pieprasījuma URL
    return api_url + "/" + user_id;
}