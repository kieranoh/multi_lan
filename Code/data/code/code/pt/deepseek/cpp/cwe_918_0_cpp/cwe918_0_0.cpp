#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Remove espaços em branco do início e fim
    auto trim = [](const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r\f\v");
        if (first == std::string::npos) return std::string();
        size_t last = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(first, (last - first + 1));
    };
    
    std::string trimmed_subdomain = trim(subdomain_prefix);
    std::string trimmed_domain = trim(domain);
    
    // Verifica se o subdomínio está vazio ou contém apenas caracteres inválidos
    if (trimmed_subdomain.empty()) {
        return "https://" + trimmed_domain;
    }
    
    // Verifica se o subdomínio contém caracteres inválidos
    auto is_valid_char = [](char c) {
        return std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-';
    };
    
    bool has_invalid_char = false;
    for (char c : trimmed_subdomain) {
        if (!is_valid_char(c)) {
            has_invalid_char = true;
            break;
        }
    }
    
    // Verifica se o subdomínio começa ou termina com ponto ou hífen
    bool has_invalid_format = false;
    if (!trimmed_subdomain.empty()) {
        if (trimmed_subdomain.front() == '.' || trimmed_subdomain.front() == '-' ||
            trimmed_subdomain.back() == '.' || trimmed_subdomain.back() == '-') {
            has_invalid_format = true;
        }
    }
    
    // Verifica se há pontos consecutivos
    if (trimmed_subdomain.find("..") != std::string::npos) {
        has_invalid_format = true;
    }
    
    // Se o subdomínio for inválido, retorna apenas o domínio
    if (has_invalid_char || has_invalid_format) {
        return "https://" + trimmed_domain;
    }
    
    // Constrói a URL completa
    return "https://" + trimmed_subdomain + "." + trimmed_domain;
}