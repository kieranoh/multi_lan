#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Check if the domain is valid
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // If the subdomain prefix is NULL or empty, return the domain itself
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Allocate memory for the final URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL;
    }

    // Create the final URL with subdomain
    snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    return url;
}