#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const size_t https_length = strlen(https_prefix);
    const size_t domain_length = strlen(domain);
    
    // Check if target starts with "https://"
    if (strncmp(target, https_prefix, https_length) == 0) {
        // Extract the domain part from the target URL
        const char* domain_start = target + https_length;
        const char* domain_end = strchr(domain_start, '/');
        size_t target_domain_length = domain_end ? (domain_end - domain_start) : strlen(domain_start);
        
        // Compare the domain part of the target with the provided domain
        if (strncmp(domain_start, domain, target_domain_length) == 0) {
            // The target URL is within the specified domain
            char* result = (char*)malloc(strlen(target) + 1);
            if (result) {
                strcpy(result, target);
            }
            return result;
        }
    }
    
    // Redirect to the domain URL
    char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
    if (result) {
        strcpy(result, https_prefix);
        strcat(result, domain);
    }
    return result;
}