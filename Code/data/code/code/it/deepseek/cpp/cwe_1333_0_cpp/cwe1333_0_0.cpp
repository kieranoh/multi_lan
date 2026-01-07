#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // Modello RFC 5322 conforme per la validazione delle email
    // Questo modello è più completo e copre più casi rispetto ai modelli semplici
    const std::string pattern = 
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    try {
        std::regex email_regex(pattern);
        
        // Controlla se la stringa corrisponde al modello
        bool is_valid = std::regex_match(email, email_regex);
        
        // Controlli aggiuntivi per evitare falsi positivi
        if (is_valid) {
            // Controlla che non ci siano due punti consecutivi
            if (email.find("..") != std::string::npos) {
                return std::make_tuple(false, pattern);
            }
            
            // Controlla che l'email non inizi o finisca con un punto
            if (email.front() == '.' || email.back() == '.') {
                return std::make_tuple(false, pattern);
            }
            
            // Trova la posizione di @
            size_t at_pos = email.find('@');
            if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
                return std::make_tuple(false, pattern);
            }
            
            // Controlla la parte locale (prima di @)
            std::string local_part = email.substr(0, at_pos);
            if (local_part.front() == '.' || local_part.back() == '.') {
                return std::make_tuple(false, pattern);
            }
            
            // Controlla la parte dominio (dopo @)
            std::string domain_part = email.substr(at_pos + 1);
            if (domain_part.front() == '.' || domain_part.back() == '.') {
                return std::make_tuple(false, pattern);
            }
            
            // Controlla che il dominio abbia almeno un punto
            if (domain_part.find('.') == std::string::npos) {
                return std::make_tuple(false, pattern);
            }
            
            // Controlla che l'ultima parte del dominio (TLD) abbia almeno 2 caratteri
            size_t last_dot = domain_part.find_last_of('.');
            if (last_dot != std::string::npos) {
                std::string tld = domain_part.substr(last_dot + 1);
                if (tld.length() < 2) {
                    return std::make_tuple(false, pattern);
                }
            }
        }
        
        return std::make_tuple(is_valid, pattern);
    }
    catch (const std::regex_error& e) {
        // In caso di errore nel modello regex, restituisci false con il modello
        return std::make_tuple(false, pattern);
    }
}