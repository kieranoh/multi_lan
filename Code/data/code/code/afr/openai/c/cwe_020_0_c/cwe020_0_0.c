#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    size_t domain_length = strlen(domain);
    
    // Check if the target URL starts with "https://"
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        // Extract the hostname from the target URL
        const char* hostname_start = target + strlen(https_prefix);
        const char* hostname_end = strchr(hostname_start, '/');
        size_t hostname_length = hostname_end ? (hostname_end - hostname_start) : strlen(hostname_start);
        
        // Check if the hostname contains the domain
        if (hostname_length >= domain_length && 
            strncmp(hostname_start, domain, domain_length) == 0) {
            return strdup(target); // Return a copy of the original target URL
        }
    }
    
    // If not in the specified domain, return the domain URL
    char* result = malloc(strlen(https_prefix) + strlen(domain) + 1);
    if (result) {
        sprintf(result, "%s%s", https_prefix, domain);
    }
    
    return result;
}