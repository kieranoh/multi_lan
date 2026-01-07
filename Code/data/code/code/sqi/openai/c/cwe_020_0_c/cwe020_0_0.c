#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_prefix = strstr(target, protocol);
    
    // Check if the target starts with the expected protocol
    if (domain_prefix != target) {
        return strdup("https://example.com");
    }
    
    // Extract the actual domain from the target URL
    const char* start = target + strlen(protocol);
    const char* end = strchr(start, '/');
    
    if (end == NULL) {
        end = start + strlen(start);
    }
    
    // Compare the actual domain with the provided domain
    char actual_domain[256];
    size_t domain_length = end - start < sizeof(actual_domain) - 1 ? end - start : sizeof(actual_domain) - 1;
    strncpy(actual_domain, start, domain_length);
    actual_domain[domain_length] = '\0';
    
    if (strstr(actual_domain, domain) != NULL) {
        return strdup(target);
    }

    return strdup("https://example.com");
}