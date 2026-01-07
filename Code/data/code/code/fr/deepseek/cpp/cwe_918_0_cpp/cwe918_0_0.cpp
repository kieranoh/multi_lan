#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Vérifier si le sous-domaine est vide ou invalide
    bool subdomain_invalid = subdomain_prefix.empty();
    
    // Vérifier si le sous-domaine contient uniquement des espaces ou caractères de contrôle
    if (!subdomain_invalid) {
        bool all_whitespace = std::all_of(subdomain_prefix.begin(), subdomain_prefix.end(), 
                                         [](unsigned char c) { return std::isspace(c); });
        subdomain_invalid = all_whitespace;
    }
    
    // Construire l'URL
    std::string url = "https://";
    
    if (!subdomain_invalid) {
        // Ajouter le préfixe de sous-domaine
        url += subdomain_prefix;
        // Ajouter le point séparateur
        url += ".";
    }
    
    // Ajouter le domaine
    url += domain;
    
    return url;
}