#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* prefix = "https://";
    const char* domain_start = strstr(target, prefix);
    
    // Check if the target starts with "https://"
    if (domain_start == target) {
        // Move the pointer past the "https://" part of the URL
        const char* domain_in_url = target + strlen(prefix);
        // Check if the domain is present in the target URL
        if (strstr(domain_in_url, domain) == domain_in_url) {
            // If it does, return the original target URL
            return strdup(target);
        }
    }
    
    // If the target URL does not belong to the domain, return the domain URL
    char* redirect_url = malloc(strlen(prefix) + strlen(domain) + 1);
    if (redirect_url == NULL) {
        return NULL; // Handle memory allocation failure
    }
    sprintf(redirect_url, "%s%s", prefix, domain);
    return redirect_url;
}