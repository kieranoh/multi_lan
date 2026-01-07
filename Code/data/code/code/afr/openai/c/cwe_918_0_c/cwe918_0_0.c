#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // If the subdomain prefix is empty or invalid, return the domain itself
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(strlen(domain) + 8); // 8 for "https://"
        if (url == NULL) {
            return NULL; // Memory allocation failed
        }
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Create the full URL
    char* url = (char*)malloc(strlen(domain) + strlen(subdomain_prefix) + 9); // 9 for "https://" and "."
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Assemble the URL
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}