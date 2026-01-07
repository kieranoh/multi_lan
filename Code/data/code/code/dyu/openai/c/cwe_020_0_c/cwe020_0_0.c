#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const char* domain_start = target + strlen(https_prefix);
    
    // Check if the target starts with "https://"
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        // Check if the target domain matches the provided domain
        if (strstr(domain_start, domain) == domain_start) {
            return strdup(target); // Return the original target
        }
    }
    
    // If the target URL is not in the domain, return the domain URL
    char* redirect_url = malloc(strlen(https_prefix) + strlen(domain) + 1);
    if (redirect_url) {
        strcpy(redirect_url, https_prefix);
        strcat(redirect_url, domain);
    }
    
    return redirect_url; // Return the constructed domain URL
}