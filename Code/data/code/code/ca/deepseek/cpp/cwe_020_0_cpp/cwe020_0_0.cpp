#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Trobar la posició del protocol
    size_t protocol_pos = target.find("://");
    if (protocol_pos == std::string::npos) {
        // Si no hi ha protocol, retornar el domini amb https
        return "https://" + domain;
    }
    
    // Extreure el domini de la target
    size_t domain_start = protocol_pos + 3;
    size_t domain_end = target.find('/', domain_start);
    std::string target_domain;
    
    if (domain_end == std::string::npos) {
        target_domain = target.substr(domain_start);
    } else {
        target_domain = target.substr(domain_start, domain_end - domain_start);
    }
    
    // Comprovar si el domini de la target acaba amb el domini donat
    bool is_within_domain = false;
    
    // Cas 1: Els dominis són exactament iguals
    if (target_domain == domain) {
        is_within_domain = true;
    }
    // Cas 2: El domini de la target és un subdomini del domini donat
    else if (target_domain.length() > domain.length() + 1) {
        size_t pos = target_domain.length() - domain.length() - 1;
        if (target_domain[pos] == '.' && 
            target_domain.substr(pos + 1) == domain) {
            is_within_domain = true;
        }
    }
    
    // Retornar el resultat
    if (is_within_domain) {
        return target;
    } else {
        return "https://" + domain;
    }
}