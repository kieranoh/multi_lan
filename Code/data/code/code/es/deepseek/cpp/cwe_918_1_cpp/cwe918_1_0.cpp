#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Verificar si el user_id está vacío o es inválido
    if (user_id.empty()) {
        return "";
    }
    
    // Verificar si el user_id contiene solo espacios en blanco
    bool all_whitespace = std::all_of(user_id.begin(), user_id.end(), [](unsigned char c) {
        return std::isspace(c);
    });
    
    if (all_whitespace) {
        return "";
    }
    
    // Construir la URL completa
    // Asegurarse de que la api_url no termine con '/'
    std::string result = api_url;
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // Añadir '/' y el user_id
    result += '/';
    result += user_id;
    
    return result;
}