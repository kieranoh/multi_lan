#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const char* domain_prefix = https_prefix + strlen(https_prefix);
    char* result;

    // Check if the target starts with the HTTPS prefix
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        // Extract the domain from the target URL
        const char* target_domain_start = target + strlen(https_prefix);
        const char* target_domain_end = strstr(target_domain_start, "/");
        size_t target_domain_length = target_domain_end ? (target_domain_end - target_domain_start) : strlen(target_domain_start);

        // Compare the extracted domain with the provided domain
        if (strncmp(target_domain_start, domain, target_domain_length) == 0 && target_domain_length == strlen(domain)) {
            // Return the original target URL
            result = malloc(strlen(target) + 1);
            strcpy(result, target);
            return result;
        }
    }

    // If the target is not in the domain, return the domain URL
    result = malloc(strlen(https_prefix) + strlen(domain) + 1);
    strcpy(result, https_prefix);
    strcat(result, domain);
    return result;
}