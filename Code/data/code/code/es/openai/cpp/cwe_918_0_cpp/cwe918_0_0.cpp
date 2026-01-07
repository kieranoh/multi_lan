#include <string>
#include <regex>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Regex para validar el subdominio
    std::regex subdomain_regex("^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\\.[A-Za-z0-9-]{1,63})*$");
    
    // Verificamos si el subdominio es válido
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain;
    }
    
    // Construimos la URL con el subdominio
    return "https://" + subdomain_prefix + "." + domain;
}