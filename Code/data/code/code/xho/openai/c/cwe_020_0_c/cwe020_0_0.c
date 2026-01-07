#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Create a string to hold the expected domain prefixed with "https://"
    char expected_domain[256];
    snprintf(expected_domain, sizeof(expected_domain), "https://%s", domain);

    // Check if the target URL starts with the expected domain
    if (strncmp(target, expected_domain, strlen(expected_domain)) == 0) {
        // The target URL is within the domain, return it as is
        return strdup(target);
    } else {
        // The target URL is not within the domain, return the domain URL
        return strdup(expected_domain);
    }
}