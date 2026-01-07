#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Prepare the base URL
    const char* protocol = "https://";
    char* url = (char*)malloc(MAX_URL_LENGTH);
    
    if (url == NULL) {
        return NULL; // Check for memory allocation failure
    }

    // Check if subdomain_prefix is empty or invalid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "%s%s", protocol, domain); // Return base domain
    } else {
        // Construct the full URL with subdomain
        snprintf(url, MAX_URL_LENGTH, "%s%s.%s", protocol, subdomain_prefix, domain);
    }

    return url; // Return the constructed URL
}