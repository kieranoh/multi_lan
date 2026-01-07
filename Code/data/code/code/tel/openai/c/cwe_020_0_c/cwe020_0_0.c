#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    size_t domain_len = strlen(domain);
    
    // Check if the target starts with the protocol
    if (strncmp(target, protocol, strlen(protocol)) == 0) {
        // Extract the URL without the protocol
        const char* url_without_protocol = target + strlen(protocol);
        
        // Check if the domain is present in the target URL
        if (strstr(url_without_protocol, domain) != NULL) {
            // If it contains the domain, return the original target
            return strdup(target);
        }
    }
    
    // If the target is not in the domain, return a new URL with the domain
    char* new_target = (char*)malloc(strlen(protocol) + domain_len + 1);
    if (new_target == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Construct the new URL
    strcpy(new_target, protocol);
    strcat(new_target, domain);
    
    return new_target;
}