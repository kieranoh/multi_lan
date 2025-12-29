#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Padrão RFC 5322 simplificado para validação de email
    // Este padrão cobre a maioria dos casos válidos enquanto evita falsos negativos
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Verifica se o email não está vazio
    if (email.empty()) {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica comprimento máximo (RFC 5321 especifica 254 caracteres no máximo)
    if (email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica se há exatamente um '@'
    int at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, pattern);
    }
    
    // Divide em parte local e domínio
    size_t at_pos = email.find('@');
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // Verifica comprimento da parte local (máximo 64 caracteres)
    if (local_part.length() > 64 || local_part.empty()) {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica se a parte local não começa ou termina com ponto
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica pontos consecutivos na parte local
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica comprimento do domínio
    if (domain_part.empty() || domain_part.length() > 253) {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica se o domínio não começa ou termina com hífen ou ponto
    if (domain_part.front() == '-' || domain_part.front() == '.' || 
        domain_part.back() == '-' || domain_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica pontos consecutivos no domínio
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Divide o domínio em labels
    std::vector<std::string> labels;
    size_t start = 0;
    size_t end = domain_part.find('.');
    
    while (end != std::string::npos) {
        labels.push_back(domain_part.substr(start, end - start));
        start = end + 1;
        end = domain_part.find('.', start);
    }
    labels.push_back(domain_part.substr(start));
    
    // Verifica cada label do domínio
    for (const auto& label : labels) {
        // Verifica comprimento de cada label (máximo 63 caracteres)
        if (label.empty() || label.length() > 63) {
            return std::make_tuple(false, pattern);
        }
        
        // Verifica se label não começa ou termina com hífen
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        
        // Verifica caracteres válidos no label do domínio
        for (char c : label) {
            if (!(std::isalnum(c) || c == '-')) {
                return std::make_tuple(false, pattern);
            }
        }
    }
    
    // Verifica se o TLD (último label) tem pelo menos 2 caracteres
    if (labels.back().length() < 2) {
        return std::make_tuple(false, pattern);
    }
    
    // Verifica se o TLD contém apenas letras
    for (char c : labels.back()) {
        if (!std::isalpha(c)) {
            return std::make_tuple(false, pattern);
        }
    }
    
    // Aplica a validação com regex como verificação final
    try {
        std::regex email_regex(pattern);
        bool is_valid = std::regex_match(email, email_regex);
        return std::make_tuple(is_valid, pattern);
    } catch (const std::regex_error&) {
        // Fallback para validação básica se houver erro no regex
        bool basic_check = (at_count == 1) && 
                          !local_part.empty() && 
                          !domain_part.empty() &&
                          (local_part.find('@') == std::string::npos) &&
                          (domain_part.find('@') == std::string::npos);
        return std::make_tuple(basic_check, pattern);
    }
}