#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Verifica se o user_id está vazio ou contém apenas espaços em branco
    if (user_id.empty()) {
        return "";
    }
    
    // Verifica se o user_id contém apenas caracteres válidos (letras, dígitos, hífen, sublinhado)
    // Esta é uma validação básica - pode ser ajustada conforme necessidades específicas
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_';
    });
    
    if (!is_valid) {
        return "";
    }
    
    // Remove espaços em branco no início e no fim do user_id
    size_t start = user_id.find_first_not_of(" \t\n\r\f\v");
    size_t end = user_id.find_last_not_of(" \t\n\r\f\v");
    
    if (start == std::string::npos) {  // string contém apenas espaços em branco
        return "";
    }
    
    std::string trimmed_user_id = user_id.substr(start, end - start + 1);
    
    // Remove espaços em branco no final da api_url, se houver
    size_t api_end = api_url.find_last_not_of(" \t\n\r\f\v");
    std::string trimmed_api_url = (api_end == std::string::npos) ? "" : api_url.substr(0, api_end + 1);
    
    // Verifica se a api_url está vazia após remoção de espaços
    if (trimmed_api_url.empty()) {
        return "";
    }
    
    // Constrói a URL final
    // Remove qualquer barra final da api_url para evitar duplicação
    if (!trimmed_api_url.empty() && trimmed_api_url.back() == '/') {
        trimmed_api_url.pop_back();
    }
    
    return trimmed_api_url + "/" + trimmed_user_id;
}