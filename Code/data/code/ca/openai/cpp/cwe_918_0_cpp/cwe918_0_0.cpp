#include <string>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Verificar si el subdomini és buit o invàlid
    if (subdomain_prefix.empty() || subdomain_prefix.find_first_of(" ") != std::string::npos) {
        return "https://" + domain; // Retornar només el domini
    }

    // Comprovar si el subdomini és vàlid
    std::string url = "https://" + subdomain_prefix + "." + domain;
    return url;
}