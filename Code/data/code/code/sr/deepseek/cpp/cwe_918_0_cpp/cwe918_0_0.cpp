#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Provera da li je poddomen prazan ili nevažeći
    bool is_subdomain_invalid = subdomain_prefix.empty();
    
    // Provera da li poddomen sadrži samo beline
    if (!is_subdomain_invalid) {
        bool only_whitespace = true;
        for (char c : subdomain_prefix) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                only_whitespace = false;
                break;
            }
        }
        is_subdomain_invalid = only_whitespace;
    }
    
    // Ako je poddomen prazan ili nevažeći, vrati samo domenu sa HTTPS
    if (is_subdomain_invalid) {
        return "https://" + domain;
    }
    
    // Ukloni vodeće i prateće beline iz poddomena
    size_t start = 0;
    size_t end = subdomain_prefix.length();
    
    while (start < end && std::isspace(static_cast<unsigned char>(subdomain_prefix[start]))) {
        start++;
    }
    
    while (end > start && std::isspace(static_cast<unsigned char>(subdomain_prefix[end - 1]))) {
        end--;
    }
    
    std::string trimmed_subdomain = subdomain_prefix.substr(start, end - start);
    
    // Ako je nakon trimovanja poddomen prazan, vrati samo domenu
    if (trimmed_subdomain.empty()) {
        return "https://" + domain;
    }
    
    // Kreiraj URL sa HTTPS protokolom
    return "https://" + trimmed_subdomain + "." + domain;
}