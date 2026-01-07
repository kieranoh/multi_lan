#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Validate the domain
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL;
    }
    
    // Check subdomain validity
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // If subdomain is empty or NULL, return the domain itself
        char* url = (char*)malloc(strlen(domain) + 8); // 8 for "https://"
        if (url == NULL) {
            return NULL; // Allocation failed
        }
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Check for invalid characters in the subdomain
    for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
        if ((subdomain_prefix[i] < 'a' || subdomain_prefix[i] > 'z') &&
            (subdomain_prefix[i] < 'A' || subdomain_prefix[i] > 'Z') &&
            (subdomain_prefix[i] < '0' || subdomain_prefix[i] > '9') &&
            subdomain_prefix[i] != '-' && subdomain_prefix[i] != '.') {
            return NULL; // Invalid character in subdomain
        }
    }

    // Create the full URL
    char* url = (char*)malloc(strlen(subdomain_prefix) + strlen(domain) + 9); // 9 for "https://"
    if (url == NULL) {
        return NULL; // Allocation failed
    }
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);

    return url;
}