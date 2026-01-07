#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    const size_t domain_length = strlen(domain);
    const size_t protocol_length = strlen(protocol);
    
    // Check if target starts with the HTTPS protocol
    if (strncmp(target, protocol, protocol_length) != 0) {
        return NULL; // Invalid URL, should start with https://
    }
    
    // Get the part of the target after the protocol
    const char* target_without_protocol = target + protocol_length;
    
    // Check if the target URL contains the domain
    if (strncmp(target_without_protocol, domain, domain_length) == 0) {
        // Return the original target URL if it matches the domain
        return strdup(target);
    }
    
    // If not matching, return the domain URL
    char* redirect_url = (char*)malloc(protocol_length + domain_length + 1);
    if (redirect_url == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Construct the redirect URL
    strcpy(redirect_url, protocol);
    strcat(redirect_url, domain);
    
    return redirect_url;
}