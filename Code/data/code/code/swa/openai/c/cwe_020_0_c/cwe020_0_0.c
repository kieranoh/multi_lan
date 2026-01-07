#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* prefix = "https://";
    const char* domain_start = strstr(target, prefix);
    
    // Check if the target starts with "https://"
    if (domain_start == target) {
        // Move pointer to the end of "https://"
        const char* domain_in_target = domain_start + strlen(prefix);
        
        // Check if the target URL contains the provided domain
        if (strstr(domain_in_target, domain) == domain_in_target || 
            strstr(domain_in_target, ".") == NULL) {
            // Valid domain, return the original target
            return strdup(target);
        }
    }
    
    // If not valid, return the domain URL
    char* redirect_url = malloc(strlen(prefix) + strlen(domain) + 1);
    if (redirect_url == NULL) {
        return NULL; // Memory allocation failed
    }
    
    strcpy(redirect_url, prefix);
    strcat(redirect_url, domain);
    
    return redirect_url;
}