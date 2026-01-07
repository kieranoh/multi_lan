#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* prefix = "https://";
    size_t prefix_len = strlen(prefix);
    size_t domain_len = strlen(domain);

    // Check if the target starts with the https://
    if (strncmp(target, prefix, prefix_len) == 0) {
        // Get the part of the target URL after "https://"
        const char* start = target + prefix_len;
        // Find the next '/' to determine the end of the domain in the target URL
        const char* end = strchr(start, '/');
        size_t domain_in_target_len = end ? (end - start) : strlen(start);

        // Compare the domain with the target's domain
        if (domain_in_target_len == domain_len && strncmp(start, domain, domain_len) == 0) {
            // The target URL is valid for redirection
            return strdup(target);
        }
    }
    
    // If the URL is not within the domain, return the domain URL
    char* redirection_url = malloc(strlen(prefix) + strlen(domain) + 1);
    if (!redirection_url) {
        return NULL; // Handle memory allocation failure
    }
    sprintf(redirection_url, "%s%s", prefix, domain);
    return redirection_url;
}