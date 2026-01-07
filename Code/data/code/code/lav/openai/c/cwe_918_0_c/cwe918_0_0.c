#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    char* url = (char*) malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // In case of memory allocation failure
    }

    // Check if the subdomain prefix is valid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url;
}