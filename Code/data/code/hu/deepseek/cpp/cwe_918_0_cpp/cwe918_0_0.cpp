#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Eltávolítjuk a szóközöket az elejéről és a végéről
    auto trim = [](const std::string& str) -> std::string {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    };
    
    std::string trimmed_domain = trim(domain);
    std::string trimmed_prefix = trim(subdomain_prefix);
    
    // Ellenőrizzük, hogy a domain üres-e
    if (trimmed_domain.empty()) {
        return "https://";
    }
    
    // Ellenőrizzük, hogy az aldomain előtag érvényes-e
    // Érvénytelen, ha üres, vagy csak whitespace karaktereket tartalmaz
    bool is_valid_subdomain = !trimmed_prefix.empty();
    
    // Ellenőrizzük, hogy az aldomain előtag csak érvényes karaktereket tartalmaz-e
    if (is_valid_subdomain) {
        auto is_valid_char = [](char c) -> bool {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '.';
        };
        
        // Ellenőrizzük, hogy minden karakter érvényes-e
        for (char c : trimmed_prefix) {
            if (!is_valid_char(c)) {
                is_valid_subdomain = false;
                break;
            }
        }
        
        // Ellenőrizzük, hogy nem kezdődik vagy végződik ponttal vagy kötőjellel
        if (is_valid_subdomain && 
            (trimmed_prefix.front() == '.' || trimmed_prefix.front() == '-' ||
             trimmed_prefix.back() == '.' || trimmed_prefix.back() == '-')) {
            is_valid_subdomain = false;
        }
        
        // Ellenőrizzük, hogy nincsenek egymás melletti pontok
        if (is_valid_subdomain && trimmed_prefix.find("..") != std::string::npos) {
            is_valid_subdomain = false;
        }
    }
    
    // Összeállítjuk az URL-t
    std::string url = "https://";
    
    if (is_valid_subdomain) {
        url += trimmed_prefix + "." + trimmed_domain;
    } else {
        url += trimmed_domain;
    }
    
    return url;
}