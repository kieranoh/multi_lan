#include <string>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    if (user_id.empty()) {
        return ""; // Retorna uma string vazia se o ID do usuário estiver vazio
    }
    return api_url + "/" + user_id; // Concatenar a URL da API com o ID do usuário
}