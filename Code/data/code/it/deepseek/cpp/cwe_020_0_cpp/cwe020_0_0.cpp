#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Controlla che i parametri non siano vuoti
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // Normalizza il dominio rimuovendo eventuali prefissi "www."
    std::string normalized_domain = domain;
    if (normalized_domain.compare(0, 4, "www.") == 0) {
        normalized_domain = normalized_domain.substr(4);
    }
    
    // Estrai l'host dalla stringa target
    std::string target_host;
    
    // Cerca il protocollo
    size_t protocol_pos = target.find("://");
    if (protocol_pos != std::string::npos) {
        // Estrai la parte dopo il protocollo
        std::string after_protocol = target.substr(protocol_pos + 3);
        
        // Trova la fine dell'host (primo '/' o fine stringa)
        size_t host_end = after_protocol.find('/');
        if (host_end != std::string::npos) {
            target_host = after_protocol.substr(0, host_end);
        } else {
            target_host = after_protocol;
        }
    } else {
        // Se non c'è protocollo, considera l'intera stringa come host
        // (ma secondo la specifica, target dovrebbe essere un URL completo)
        size_t host_end = target.find('/');
        if (host_end != std::string::npos) {
            target_host = target.substr(0, host_end);
        } else {
            target_host = target;
        }
    }
    
    // Normalizza l'host target rimuovendo eventuali prefissi "www."
    std::string normalized_target_host = target_host;
    if (normalized_target_host.compare(0, 4, "www.") == 0) {
        normalized_target_host = normalized_target_host.substr(4);
    }
    
    // Controlla se l'host target termina con il dominio specificato
    bool is_within_domain = false;
    
    // Caso 1: host target è esattamente uguale al dominio
    if (normalized_target_host == normalized_domain) {
        is_within_domain = true;
    }
    // Caso 2: host target termina con "." + dominio (sottodominio)
    else if (normalized_target_host.length() > normalized_domain.length() + 1) {
        size_t pos = normalized_target_host.length() - normalized_domain.length() - 1;
        if (normalized_target_host[pos] == '.' && 
            normalized_target_host.substr(pos + 1) == normalized_domain) {
            is_within_domain = true;
        }
    }
    
    // Se è all'interno del dominio, restituisci l'URL target con protocollo https
    if (is_within_domain) {
        // Assicurati che l'URL target inizi con https://
        if (target.compare(0, 8, "https://") == 0) {
            return target;
        } else if (target.compare(0, 7, "http://") == 0) {
            // Sostituisci http:// con https://
            return "https://" + target.substr(7);
        } else if (target.find("://") == std::string::npos) {
            // Se non c'è protocollo, aggiungi https://
            return "https://" + target;
        } else {
            // Se c'è un altro protocollo, sostituiscilo con https://
            size_t protocol_end = target.find("://");
            return "https://" + target.substr(protocol_end + 3);
        }
    } else {
        // Altrimenti, restituisci il dominio con https://
        return "https://" + domain;
    }
}