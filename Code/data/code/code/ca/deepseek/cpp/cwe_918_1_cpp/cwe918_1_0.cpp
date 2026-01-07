#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Comprovar si l'ID d'usuari és buit
    if (user_id.empty()) {
        return "";
    }
    
    // Comprovar si l'ID d'usuari conté només caràcters vàlids (alfanumèrics i alguns símbols comuns)
    // Això és una comprovació bàsica; pots ajustar-la segons els teus requisits
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.';
    });
    
    if (!is_valid) {
        return "";
    }
    
    // Construir la URL de consulta
    // Assegurar-nos que la URL de l'API no tingui una barra diagonal al final
    std::string result = api_url;
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Afegir l'ID d'usuari a la URL
    result += "/" + user_id;
    
    return result;
}