#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    char* domain_with_https;
    size_t domain_length = strlen(domain);
    size_t target_length = strlen(target);
    
    // Allocate memory for domain URL with https prefix
    domain_with_https = (char*)malloc(domain_length + strlen(https_prefix) + 1);
    if (domain_with_https == NULL) {
        return NULL; // Handle memory allocation failure
    }
    
    // Construct the domain URL with https
    strcpy(domain_with_https, https_prefix);
    strcat(domain_with_https, domain);
    
    // Check if target starts with the domain URL or any subdomain
    if (strncmp(target, domain_with_https, strlen(domain_with_https)) == 0) {
        free(domain_with_https); // Free allocated memory
        return strdup(target); // Return a duplicate of the target
    } else {
        free(domain_with_https); // Free allocated memory
        return domain_with_https; // Return the domain URL
    }
}