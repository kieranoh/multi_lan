#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256

// Function to check if a subdomain is valid
bool is_valid_subdomain(const char* subdomain) {
    // Check for NULL or empty string
    if (subdomain == NULL || *subdomain == '\0') {
        return false;
    }
    
    // Check for invalid characters
    for (const char* p = subdomain; *p; p++) {
        if (!(((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || (*p == '-') || (*p == '.')))) {
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

    // Check if the subdomain is valid
    if (is_valid_subdomain(subdomain_prefix)) {
        // Generate the URL with subdomain
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // Fallback to the domain itself
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url; // Return the generated URL
}