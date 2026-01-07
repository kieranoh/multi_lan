#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_start = strstr(target, protocol);
    
    if (domain_start != NULL) {
        domain_start += strlen(protocol);
        const char* domain_end = strchr(domain_start, '/');
        
        size_t target_domain_length = domain_end ? (domain_end - domain_start) : strlen(domain_start);
        if (strncmp(domain_start, domain, target_domain_length) == 0 && 
            (target_domain_length == strlen(domain) || 
            (target_domain_length > strlen(domain) && domain_start[strlen(domain)] == '.'))) {
            return strdup(target); // Valid domain, return original target
        }
    }
    
    // If target URL is not in the specified domain, return default domain URL
    size_t domain_url_length = strlen(protocol) + strlen(domain) + 1; // +1 for null terminator
    char* redirect_url = (char*)malloc(domain_url_length);
    if (redirect_url != NULL) {
        sprintf(redirect_url, "%s%s", protocol, domain);
    }
    return redirect_url;
}