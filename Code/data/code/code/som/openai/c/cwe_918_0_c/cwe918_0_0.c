#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Validate inputs
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // If subdomain_prefix is NULL or empty, return the domain as a URL
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(strlen(domain) + 8); // "https://" + domain
        if (url != NULL) {
            sprintf(url, "https://%s", domain);
        }
        return url;
    }

    // Check if the subdomain_prefix contains invalid characters (e.g., spaces)
    for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
        if (subdomain_prefix[i] == ' ') {
            return NULL; // Invalid subdomain
        }
    }

    // Prepare the final URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    return url;
}