#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Patrón de expresión regular para validar direcciones de correo electrónico según RFC 5322
    // Este patrón cubre la mayoría de casos válidos mientras evita falsos negativos
    std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+)"
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    // Verificar longitud básica (mínimo: a@b.c, máximo: 254 caracteres según RFC)
    if (email.empty() || email.length() > 254 || email.length() < 5) {
        return std::make_tuple(false, pattern);
    }
    
    // Verificar que haya exactamente un símbolo '@'
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Verificar que el dominio tenga al menos un punto después del '@'
    std::string domain = email.substr(at_pos + 1);
    if (domain.find('.') == std::string::npos || domain.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Verificar que no haya puntos consecutivos en el dominio
    if (domain.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Verificar que la parte local (antes del @) no esté vacía
    std::string local_part = email.substr(0, at_pos);
    if (local_part.empty() || local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // Verificar que no haya puntos consecutivos en la parte local
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // Verificar caracteres válidos usando expresión regular
    try {
        std::regex email_regex(pattern);
        bool is_valid = std::regex_match(email, email_regex);
        
        // Verificación adicional para TLD (Top-Level Domain)
        if (is_valid) {
            // Extraer el último segmento del dominio (TLD)
            size_t last_dot = domain.rfind('.');
            std::string tld = domain.substr(last_dot + 1);
            
            // El TLD debe tener al menos 2 caracteres y solo letras
            if (tld.length() < 2 || !std::all_of(tld.begin(), tld.end(), 
                [](char c) { return std::isalpha(static_cast<unsigned char>(c)); })) {
                return std::make_tuple(false, pattern);
            }
            
            // Verificar que el dominio no tenga guiones al inicio o final de segmentos
            std::string domain_without_tld = domain.substr(0, last_dot);
            size_t dash_pos = domain_without_tld.find('-');
            while (dash_pos != std::string::npos) {
                if (dash_pos == 0 || dash_pos == domain_without_tld.length() - 1 || 
                    domain_without_tld[dash_pos - 1] == '.' || 
                    domain_without_tld[dash_pos + 1] == '.') {
                    return std::make_tuple(false, pattern);
                }
                dash_pos = domain_without_tld.find('-', dash_pos + 1);
            }
        }
        
        return std::make_tuple(is_valid, pattern);
    }
    catch (const std::regex_error&) {
        // En caso de error en la expresión regular, usar validación básica
        bool basic_valid = (at_pos > 0 && at_pos < email.length() - 1 &&
                           email.find(' ') == std::string::npos &&
                           email.find("..") == std::string::npos);
        return std::make_tuple(basic_valid, pattern);
    }
}