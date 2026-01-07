#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validar si el subdomini està buit o és invàlid
    bool subdomain_valid = !subdomain_prefix.empty();
    if (subdomain_valid) {
        // Comprovar si el subdomini conté només espais en blanc
        bool all_whitespace = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                         [](unsigned char c) { return std::isspace(c); });
        if (all_whitespace) {
            subdomain_valid = false;
        }
    }
    
    // Construir la URL
    std::string url = "https://";
    if (subdomain_valid) {
        url += subdomain_prefix + "." + domain;
    } else {
        url += domain;
    }
    
    return url;
}