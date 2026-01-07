#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Check if the target URL starts with "https://"
    const char* prefix = "https://";
    if (strncmp(target, prefix, strlen(prefix)) != 0) {
        return NULL; // Invalid target URL, must start with "https://"
    }

    // Check if the domain is present in the target URL
    // We need to ensure the domain matches correctly
    char* domain_with_prefix = malloc(strlen(prefix) + strlen(domain) + 1);
    if (domain_with_prefix == NULL) {
        return NULL; // Memory allocation failed
    }
    strcpy(domain_with_prefix, prefix);
    strcat(domain_with_prefix, domain);

    // Check if the target starts with the domain URL
    if (strncmp(target, domain_with_prefix, strlen(domain_with_prefix)) == 0) {
        free(domain_with_prefix);
        return strdup(target); // Return the original target URL
    }

    // If the target URL does not belong to the domain, return the domain URL
    free(domain_with_prefix);
    return strdup(domain_with_prefix); // Return the domain URL
}