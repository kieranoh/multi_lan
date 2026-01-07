#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    size_t domain_length = strlen(domain);
    
    // Sprawdź, czy docelowy URL zaczyna się od protokołu
    if (strncmp(target, protocol, strlen(protocol)) == 0) {
        const char* url_domain_start = target + strlen(protocol);
        
        // Znajdź pozycję pierwszego ukośnika po protokole
        const char* url_domain_end = strchr(url_domain_start, '/');
        size_t url_domain_length = url_domain_end ? (url_domain_end - url_domain_start) : strlen(url_domain_start);
        
        // Porównaj domeny
        if (strncmp(url_domain_start, domain, domain_length) == 0 && 
            (url_domain_length == domain_length || url_domain_start[domain_length] == '.')) {
            // Jeśli URL docelowy znajduje się w podanej domenie
            return strdup(target);
        }
    }
    
    // W przeciwnym razie, zwróć URL domeny do przekierowania
    char* redirect_url = malloc(strlen(protocol) + domain_length + 1);
    if (redirect_url) {
        sprintf(redirect_url, "%s%s", protocol, domain);
    }
    
    return redirect_url;
}