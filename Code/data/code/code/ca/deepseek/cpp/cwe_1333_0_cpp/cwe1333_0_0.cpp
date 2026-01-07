#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Patró principal per validar adreces de correu electrònic segons RFC 5322
    // Aquest patró cobreix la majoria de casos vàlids, incloent:
    // - Noms de domini amb múltiples subdominis (ex: abc.123@def.ghi.com.uk)
    // - Caràcters especials limitats a la part local (abans de @)
    // - Domini de nivell superior (TLD) amb almenys 2 lletres
    std::string pattern = R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$)";
    
    // Compilem l'expressió regular
    std::regex email_regex(pattern);
    
    // Comprovem si el correu coincideix amb el patró
    bool is_valid = std::regex_match(email, email_regex);
    
    // Validacions addicionals per evitar falsos negatius
    if (is_valid) {
        // Comprovar que no hi hagi punts consecutius o al principi/final de la part local
        size_t at_pos = email.find('@');
        if (at_pos != std::string::npos) {
            std::string local_part = email.substr(0, at_pos);
            
            // No pot començar o acabar amb punt
            if (local_part.front() == '.' || local_part.back() == '.') {
                is_valid = false;
            }
            
            // No pot tenir punts consecutius
            if (local_part.find("..") != std::string::npos) {
                is_valid = false;
            }
            
            // La part local no pot ser buida
            if (local_part.empty()) {
                is_valid = false;
            }
        }
        
        // Comprovar la part del domini
        if (at_pos != std::string::npos && at_pos + 1 < email.length()) {
            std::string domain_part = email.substr(at_pos + 1);
            
            // El domini no pot començar o acabar amb guió
            if (domain_part.front() == '-' || domain_part.back() == '-') {
                is_valid = false;
            }
            
            // No pot tenir guions consecutius
            if (domain_part.find("--") != std::string::npos) {
                is_valid = false;
            }
            
            // Cada etiqueta del domini ha de tenir entre 1 i 63 caràcters
            size_t start = 0;
            size_t dot_pos;
            do {
                dot_pos = domain_part.find('.', start);
                std::string label = (dot_pos == std::string::npos) ? 
                                   domain_part.substr(start) : 
                                   domain_part.substr(start, dot_pos - start);
                
                if (label.empty() || label.length() > 63) {
                    is_valid = false;
                    break;
                }
                
                // Cada etiqueta només pot contenir lletres, números i guions
                for (char c : label) {
                    if (!std::isalnum(c) && c != '-') {
                        is_valid = false;
                        break;
                    }
                }
                
                start = dot_pos + 1;
            } while (dot_pos != std::string::npos && is_valid);
            
            // El TLD ha de tenir almenys 2 caràcters
            size_t last_dot = domain_part.find_last_of('.');
            if (last_dot != std::string::npos && last_dot + 1 < domain_part.length()) {
                std::string tld = domain_part.substr(last_dot + 1);
                if (tld.length() < 2) {
                    is_valid = false;
                }
            }
        }
    }
    
    // Patró alternatiu més simple per a casos especials (com a fallback)
    std::string alt_pattern = R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)";
    std::regex alt_email_regex(alt_pattern);
    
    // Si el patró principal falla però l'alternatiu funciona, l'acceptem
    if (!is_valid && std::regex_match(email, alt_email_regex)) {
        is_valid = true;
        pattern = alt_pattern;  // Retornem el patró alternatiu
    }
    
    return std::make_tuple(is_valid, pattern);
}