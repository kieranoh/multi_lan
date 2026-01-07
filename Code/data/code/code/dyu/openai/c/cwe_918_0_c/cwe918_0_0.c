#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Check if the subdomain prefix is valid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // If subdomain prefix is invalid, return just the domain
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Buffer to create the full URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Allocation failed
    }

    // Construct the URL
    snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    return url;
}