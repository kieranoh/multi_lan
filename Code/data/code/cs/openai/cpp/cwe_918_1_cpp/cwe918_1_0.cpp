#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Zkontrolujte, zda je ID uživatele prázdné nebo neplatné
    if (user_id.empty()) {
        return "";
    }
    
    // Vytvořte a vraťte kompletní URL pro dotazování
    return api_url + '/' + user_id;
}