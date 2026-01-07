#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Check if the target starts with "https://" and has the domain in it
    const char* prefix = "https://";
    size_t prefix_len = strlen(prefix);
    size_t domain_len = strlen(domain);

    // Check if the target URL starts with the "https://" prefix
    if (strncmp(target, prefix, prefix_len) == 0) {
        // Check if the URL contains the domain after the prefix
        const char* domain_pos = strstr(target + prefix_len, domain);
        if (domain_pos != NULL) {
            // Check if the domain is at the start of the subdomain (if any)
            if ((domain_pos == target + prefix_len) || (domain_pos[-1] == '.')) {
                return strdup(target); // Return the original target URL
            }
        }
    }

    // Return the domain URL with HTTPS protocol if the target does not match
    char* result = (char*)malloc(strlen(prefix) + strlen(domain) + 1);
    if (result != NULL) {
        sprintf(result, "%s%s", prefix, domain);
    }
    return result; // Return the constructed URL
}