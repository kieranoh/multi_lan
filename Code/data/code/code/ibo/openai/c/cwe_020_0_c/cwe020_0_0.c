#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_start = strstr(target, protocol);
    
    if (domain_start != NULL) {
        domain_start += strlen(protocol);
        char* end_of_domain = strchr(domain_start, '/');
        size_t domain_length = end_of_domain ? (size_t)(end_of_domain - domain_start) : strlen(domain_start);

        if (strncmp(domain_start, domain, domain_length) == 0 && (domain_length == strlen(domain) || domain[domain_length] == '.')) {
            return strdup(target);
        }
    }
    
    // If not in the domain, return the domain URL
    char* redirect_url = malloc(strlen(protocol) + strlen(domain) + 1);
    if (redirect_url == NULL) {
        return NULL; // Memory allocation failed
    }
    sprintf(redirect_url, "%s%s", protocol, domain);
    return redirect_url;
}