#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* http_prefix = "https://";
    size_t target_length = strlen(target);
    size_t domain_length = strlen(domain);
    char* result = NULL;

    // Check if the target starts with the https prefix
    if (strncmp(target, http_prefix, strlen(http_prefix)) == 0) {
        const char* domain_start = target + strlen(http_prefix);
        // Check if the target contains the domain
        if (strncmp(domain_start, domain, domain_length) == 0) {
            // Valid target domain
            result = malloc(target_length + 1);
            if (result) {
                strcpy(result, target);
            }
        }
    }

    // If the target URL is not in the specified domain, return the domain URL
    if (result == NULL) {
        result = malloc(strlen(http_prefix) + domain_length + 1);
        if (result) {
            strcpy(result, http_prefix);
            strcat(result, domain);
        }
    }

    return result;
}