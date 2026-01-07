#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Check if the domain is NULL or empty
    if (domain == NULL || strlen(domain) == 0) {
        return NULL; // Invalid domain
    }
    
    // If subdomain_prefix is NULL or empty, return the domain as URL
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(strlen(domain) + 8); // 8 for "https://"
        if (url == NULL) return NULL; // Memory allocation failure
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Construct the URL with the given subdomain prefix
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) return NULL; // Memory allocation failure

    // Format the URL as "https://subdomain.domain"
    snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    return url;
}