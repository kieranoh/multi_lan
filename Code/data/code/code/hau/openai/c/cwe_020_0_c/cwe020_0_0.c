#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Check if the target starts with "https://"
    if (strncmp(target, "https://", 8) != 0) {
        return NULL; // Invalid target URL
    }

    // Create a string to hold the domain with "https://" prefix
    char* full_domain = malloc(strlen("https://") + strlen(domain) + 1);
    if (full_domain == NULL) {
        return NULL; // Memory allocation failed
    }
    strcpy(full_domain, "https://");
    strcat(full_domain, domain);

    // Check if the target URL contains the domain
    if (strstr(target, full_domain) == target) {
        free(full_domain); // Free allocated memory
        return strdup(target); // Return the original target URL
    } else {
        free(full_domain); // Free allocated memory
        return strdup(full_domain); // Return the domain URL
    }
}