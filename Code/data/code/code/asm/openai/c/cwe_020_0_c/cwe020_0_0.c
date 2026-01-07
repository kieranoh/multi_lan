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
            return strdup(target);
        }
    }
    
    size_t domain_url_length = strlen(protocol) + strlen(domain) + 1; // +1 for '\0'
    char* result = malloc(domain_url_length);
    if (result) {
        snprintf(result, domain_url_length, "%s%s", protocol, domain);
    }
    return result;
}