#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Kontrola, zda je subdoména prázdná nebo neplatná
    bool is_subdomain_invalid = subdomain_prefix.empty();
    
    // Pokud není prázdná, zkontrolujte, zda obsahuje pouze mezery nebo neplatné znaky
    if (!is_subdomain_invalid) {
        // Zkontrolujte, zda obsahuje pouze mezery
        bool all_spaces = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                     [](unsigned char c) { return std::isspace(c); });
        
        // Zkontrolujte, zda obsahuje neplatné znaky pro subdoménu
        bool has_invalid_chars = std::any_of(subdomain_prefix.begin(), subdomain_prefix.end(),
                                           [](unsigned char c) {
                                               return !(std::isalnum(c) || c == '-' || c == '.');
                                           });
        
        is_subdomain_invalid = all_spaces || has_invalid_chars;
    }
    
    // Sestavení URL
    std::string url = "https://";
    
    if (!is_subdomain_invalid) {
        url += subdomain_prefix;
        url += ".";
    }
    
    url += domain;
    
    return url;
}