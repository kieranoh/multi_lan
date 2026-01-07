#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Verificar si el subdominio es válido (no vacío y no solo espacios)
    bool subdomain_valid = false;
    if (!subdomain_prefix.empty()) {
        // Verificar si contiene al menos un carácter no espacio
        if (std::any_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                       [](char c) { return !std::isspace(static_cast<unsigned char>(c)); })) {
            subdomain_valid = true;
        }
    }
    
    // Construir la URL
    std::string url = "https://";
    
    if (subdomain_valid) {
        // Agregar el prefijo del subdominio
        url += subdomain_prefix;
        // Agregar un punto solo si el subdominio no termina con punto
        if (!subdomain_prefix.empty() && subdomain_prefix.back() != '.') {
            url += '.';
        }
    }
    
    // Agregar el dominio
    url += domain;
    
    return url;
}