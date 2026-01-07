#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* http_prefix = "https://";
    const char* domain_with_prefix = http_prefix + strlen(http_prefix);
    
    // Check if target starts with "https://"
    if (strncmp(target, http_prefix, strlen(http_prefix)) == 0) {
        // Get the domain part of the target URL
        const char* start_of_domain = target + strlen(http_prefix);
        const char* end_of_domain = strchr(start_of_domain, '/');
        
        size_t domain_length = (end_of_domain != NULL) ? (end_of_domain - start_of_domain) : strlen(start_of_domain);
        
        // Check if the domain in the target matches the provided domain
        if (strncmp(start_of_domain, domain, domain_length) == 0 && 
            (domain_length == strlen(domain) || (*(start_of_domain + domain_length) == '.'))) {
            return strdup(target); // Return the target URL
        }
    }
    
    // If not matching, redirect to the domain
    char* redirect_url = (char*)malloc(strlen(http_prefix) + strlen(domain) + 1);
    if (redirect_url) {
        strcpy(redirect_url, http_prefix);
        strcat(redirect_url, domain);
    }
    
    return redirect_url; // Return the default domain URL
}