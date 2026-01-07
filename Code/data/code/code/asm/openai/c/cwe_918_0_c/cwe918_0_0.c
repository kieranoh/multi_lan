#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Check if the subdomain prefix is valid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // If the subdomain is empty or NULL, use the domain itself
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Construct the URL with the provided subdomain prefix
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url;
}