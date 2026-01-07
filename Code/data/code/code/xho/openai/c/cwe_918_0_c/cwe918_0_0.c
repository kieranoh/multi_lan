#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Check if the subdomain_prefix is empty or invalid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // If subdomain is empty, return just the domain
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Validate the subdomain prefix (you can add more validation as needed)
        if (strchr(subdomain_prefix, '.') != NULL) {
            // Concatenate with subdomains containing a dot
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        } else {
            // Concatenate the simple subdomain
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        }
    }

    return url;
}