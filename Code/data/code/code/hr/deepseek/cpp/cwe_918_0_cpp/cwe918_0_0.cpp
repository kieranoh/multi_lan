#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Provjera je li poddomena prazna ili nevažeća
    bool subdomain_valid = false;
    if (!subdomain_prefix.empty()) {
        // Provjera sadrži li poddomena barem jedan alfanumerički znak
        subdomain_valid = std::any_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                      [](char c) { return std::isalnum(static_cast<unsigned char>(c)); });
    }
    
    // Izgradi URL
    std::string url = "https://";
    
    if (subdomain_valid) {
        // Dodaj poddomenu i točku
        url += subdomain_prefix + ".";
    }
    
    // Dodaj domenu
    url += domain;
    
    return url;
}