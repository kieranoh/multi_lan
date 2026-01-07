#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_start = strstr(target, protocol);
    
    if (domain_start) {
        domain_start += strlen(protocol);
        const char* domain_end = strchr(domain_start, '/');
        size_t domain_length = domain_end ? (domain_end - domain_start) : strlen(domain_start);
        
        if (strncmp(domain_start, domain, domain_length) == 0 && 
            (domain_length == strlen(domain) || domain[domain_length] == '.')) {
            // The target URL is in the provided domain
            return strdup(target);
        }
    }
    
    // Replace with the domain URL
    char* redirect_url = (char*)malloc(strlen(protocol) + strlen(domain) + 1);
    if (redirect_url) {
        sprintf(redirect_url, "%s%s", protocol, domain);
    }
    
    return redirect_url;
}