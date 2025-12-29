#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const char* domain_with_protocol = NULL;
    size_t target_len = strlen(target);
    size_t domain_len = strlen(domain);
    
    // Check if the target starts with the protocol
    if (strncmp(target, protocol, strlen(protocol)) == 0) {
        // Extract the domain from the target URL
        const char* start = target + strlen(protocol);
        const char* end = strstr(start, "/");
        size_t actual_domain_len = (end != NULL) ? (end - start) : strlen(start);
        
        // If target domain matches
        if (actual_domain_len == domain_len && strncmp(start, domain, domain_len) == 0) {
            // Return the target URL as it is within the domain
            char* result = (char*)malloc(target_len + 1);
            if (result == NULL) {
                return NULL; // Memory allocation failed
            }
            strcpy(result, target);
            return result;
        }
    }
    
    // Fallback to the domain URL
    size_t redirect_url_len = strlen(protocol) + domain_len + 1; // +1 for null terminator
    char* redirect_url = (char*)malloc(redirect_url_len);
    if (redirect_url == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Construct the redirect URL
    strcpy(redirect_url, protocol);
    strcat(redirect_url, domain);
    
    return redirect_url;
}