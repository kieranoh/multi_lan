#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256

// Helper function to check if a subdomain prefix is valid
bool is_valid_subdomain(const char* subdomain_prefix) {
    // Check for NULL or empty
    if (subdomain_prefix == NULL || *subdomain_prefix == '\0') {
        return false;
    }
    // Check for invalid characters (for simplicity, we allow alphanumeric and dots)
    for (const char* p = subdomain_prefix; *p; ++p) {
        if (!(((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
               (*p >= '0' && *p <= '9') || *p == '.'))) {
            return false;
        }
    }
    return true;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // If the subdomain is valid, construct the URL with subdomain
    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // Otherwise, just use the domain
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}