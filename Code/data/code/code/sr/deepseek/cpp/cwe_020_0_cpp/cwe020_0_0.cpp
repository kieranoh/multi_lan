#include <string>
#include <cctype>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Proveravamo da li target počinje sa "https://"
    const std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // Ako ne počinje sa https://, vraćamo https:// + domain
        return https_prefix + domain;
    }
    
    // Ekstraktujemo host iz target URL-a (deo posle https:// do prvog '/' ili kraja stringa)
    std::string target_host;
    size_t host_start = https_prefix.length();
    size_t host_end = target.find('/', host_start);
    
    if (host_end == std::string::npos) {
        target_host = target.substr(host_start);
    } else {
        target_host = target.substr(host_start, host_end - host_start);
    }
    
    // Proveravamo da li target_host završava sa domain
    // Prvo proveravamo da li je target_host jednak domain
    if (target_host == domain) {
        return target;
    }
    
    // Proveravamo da li target_host završava sa "." + domain
    if (target_host.length() > domain.length() + 1) {
        size_t dot_pos = target_host.length() - domain.length() - 1;
        if (target_host[dot_pos] == '.' && 
            target_host.substr(dot_pos + 1) == domain) {
            return target;
        }
    }
    
    // Ako nije unutar domena, vraćamo https:// + domain
    return https_prefix + domain;
}