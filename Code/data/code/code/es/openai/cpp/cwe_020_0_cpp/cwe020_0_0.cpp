#include <string>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Construir la URL del dominio con el protocolo https
    std::string domain_url = "https://" + domain;

    // Verificar si la URL objetivo comienza con el dominio
    if (target.find(domain_url) == 0 || target == domain_url) {
        return target;  // Devuelve la URL objetivo si está dentro del dominio
    }
    
    return domain_url;  // Devuelve la URL del dominio si la URL objetivo no está en el dominio
}