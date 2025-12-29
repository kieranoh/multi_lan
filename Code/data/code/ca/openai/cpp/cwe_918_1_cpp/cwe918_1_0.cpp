#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Comprovem si l'ID d'usuari és buit o invàlid
    if (user_id.empty()) {
        return ""; // Retornem una cadena buida
    }
    
    // Generem la URL per a la consulta
    return api_url + "/" + user_id; // Retornem la URL concatenada
}