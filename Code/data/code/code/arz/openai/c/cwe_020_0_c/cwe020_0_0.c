#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char *protocol = "https://";
    const char *domain_with_protocol = protocol;
    
    // Construct the full domain URL
    char *full_domain_url = malloc(strlen(domain_with_protocol) + strlen(domain) + 1);
    if (full_domain_url == NULL) {
        return NULL; // Memory allocation failed
    }
    strcpy(full_domain_url, domain_with_protocol);
    strcat(full_domain_url, domain);
    
    // Check if the target URL contains the domain
    if (strstr(target, full_domain_url) == target) {
        // If the target URL starts with the domain URL, return the target URL
        free(full_domain_url);
        return strdup(target); // Return a new allocated string
    } else {
        // If not, return the domain URL
        free(full_domain_url);
        return strdup(full_domain_url); // Return a new allocated string
    }
}