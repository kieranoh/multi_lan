#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Check if the domain is valid
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // If the subdomain prefix is empty or invalid, return the domain URL
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Validate and construct the URL with the subdomain prefix
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}