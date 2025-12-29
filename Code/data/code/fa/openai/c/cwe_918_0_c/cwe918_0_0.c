#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the resulting URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Check if the subdomain_prefix is valid
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // Check if it contains invalid characters (e.g., spaces)
        if (strpbrk(subdomain_prefix, " /\\") != NULL) {
            // Invalid subdomain; return the domain only
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        } else {
            // Valid subdomain; construct the full URL
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        }
    } else {
        // No valid subdomain; return the domain only
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}