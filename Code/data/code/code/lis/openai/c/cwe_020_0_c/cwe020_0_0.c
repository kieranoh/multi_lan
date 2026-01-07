#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_start = strstr(target, protocol);
    
    if (domain_start == NULL) {
        return strdup("https://example.com");
    }
    
    domain_start += strlen(protocol);
    
    // Check if the target URL starts with the provided domain
    if (strncmp(domain_start, domain, strlen(domain)) == 0) {
        return strdup(target); // The target is within the domain
    } else {
        return strdup("https://example.com"); // The target is outside the domain
    }
}