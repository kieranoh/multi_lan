#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    std::string https_prefix = "https://";
    std::string domain_with_https = https_prefix + domain;
    
    // Verifica si l'URL de destinació comença amb el prefix https:// i si conté el domini
    if (target.find(https_prefix) == 0 && target.find(domain) != std::string::npos) {
        return target; // Retorna l'URL de destinació si es troba dins del domini
    }
    
    return domain_with_https; // Retorna l'URL del domini per a la redirecció
}