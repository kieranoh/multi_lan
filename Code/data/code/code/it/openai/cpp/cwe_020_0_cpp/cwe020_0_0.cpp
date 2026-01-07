#include <string>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Verifica se l'URL di destinazione inizia con "https://" 
    if (target.find("https://") == 0) {
        // Estrae il dominio dall'URL di destinazione
        std::size_t start = target.find("://") + 3; // Aggiunge 3 per saltare "https://"
        std::size_t end = target.find('/', start);
        std::string target_domain = (end == std::string::npos) ? target.substr(start) : target.substr(start, end - start);
        
        // Controlla se il dominio dell'URL di destinazione corrisponde al dominio fornito
        if (target_domain == domain || target_domain.ends_with("." + domain)) {
            return target; // Restituisce l'URL di destinazione se il dominio è corretto
        }
    }
    
    // Se non corrisponde, restituisce l'URL del dominio con protocollo https
    return "https://" + domain;
}