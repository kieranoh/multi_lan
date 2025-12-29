#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Rimuove gli spazi bianchi all'inizio e alla fine
    auto trim = [](const std::string& str) -> std::string {
        size_t first = str.find_first_not_of(" \t\n\r\f\v");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(first, (last - first + 1));
    };
    
    std::string trimmed_domain = trim(domain);
    std::string trimmed_prefix = trim(subdomain_prefix);
    
    // Controlla se il sottodominio è vuoto o non valido
    bool is_subdomain_valid = !trimmed_prefix.empty();
    if (is_subdomain_valid) {
        // Controlla se il sottodominio contiene solo caratteri validi
        // Permette lettere, numeri, punti e trattini (come nei nomi di dominio standard)
        for (char c : trimmed_prefix) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
                is_subdomain_valid = false;
                break;
            }
        }
        // Controlla che non inizi o finisca con un punto o trattino
        if (!trimmed_prefix.empty() && 
            (trimmed_prefix.front() == '.' || trimmed_prefix.front() == '-' ||
             trimmed_prefix.back() == '.' || trimmed_prefix.back() == '-')) {
            is_subdomain_valid = false;
        }
        // Controlla che non ci siano due punti consecutivi
        if (trimmed_prefix.find("..") != std::string::npos) {
            is_subdomain_valid = false;
        }
    }
    
    // Costruisce l'URL
    std::string url = "https://";
    
    if (is_subdomain_valid) {
        url += trimmed_prefix + "." + trimmed_domain;
    } else {
        url += trimmed_domain;
    }
    
    return url;
}