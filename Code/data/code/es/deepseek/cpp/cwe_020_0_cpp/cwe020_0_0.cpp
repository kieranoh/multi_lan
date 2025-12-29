#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Verificar que los parámetros no estén vacíos
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Convertir a minúsculas para comparación insensible a mayúsculas/minúsculas
    auto to_lower = [](const std::string& str) {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        return lower_str;
    };
    
    std::string target_lower = to_lower(target);
    std::string domain_lower = to_lower(domain);
    
    // Encontrar la posición del protocolo
    size_t protocol_pos = target_lower.find("https://");
    if (protocol_pos == std::string::npos) {
        // Si no tiene protocolo https, usar el dominio proporcionado
        return "https://" + domain;
    }
    
    // Extraer la parte del host de la URL
    size_t host_start = protocol_pos + 8; // Longitud de "https://"
    size_t host_end = target_lower.find('/', host_start);
    
    std::string host;
    if (host_end == std::string::npos) {
        host = target_lower.substr(host_start);
    } else {
        host = target_lower.substr(host_start, host_end - host_start);
    }
    
    // Verificar si el host termina con el dominio proporcionado
    if (host == domain_lower || 
        (host.length() > domain_lower.length() + 1 && 
         host.substr(host.length() - domain_lower.length() - 1) == "." + domain_lower)) {
        // Si el host coincide exactamente o es un subdominio del dominio
        return target; // Devolver la URL original (conservando mayúsculas/minúsculas)
    }
    
    // Si no coincide, redirigir al dominio base
    return "https://" + domain;
}