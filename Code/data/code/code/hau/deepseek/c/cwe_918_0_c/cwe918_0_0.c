#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (!url) return NULL;
    
    // Initialize URL with HTTPS protocol
    strcpy(url, "https://");
    
    // Check if subdomain_prefix is valid (not NULL, not empty, and contains valid characters)
    if (subdomain_prefix && subdomain_prefix[0] != '\0') {
        // Validate subdomain prefix - must contain only alphanumeric characters, dots, and hyphens
        int valid = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
        }
        
        // Check that subdomain doesn't start or end with dot or hyphen
        if (valid && strlen(subdomain_prefix) > 0) {
            char first = subdomain_prefix[0];
            char last = subdomain_prefix[strlen(subdomain_prefix) - 1];
            if (first == '.' || first == '-' || last == '.' || last == '-') {
                valid = 0;
            }
        }
        
        // Check for consecutive dots or hyphens
        if (valid) {
            for (int i = 0; subdomain_prefix[i] != '\0' && subdomain_prefix[i + 1] != '\0'; i++) {
                if ((subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') ||
                    (subdomain_prefix[i] == '-' && subdomain_prefix[i + 1] == '-')) {
                    valid = 0;
                    break;
                }
            }
        }
        
        // If subdomain is valid, construct URL with subdomain
        if (valid) {
            // Check if we have enough space for the full URL
            int needed_length = strlen("https://") + strlen(subdomain_prefix) + 1 + strlen(domain) + 1;
            if (needed_length <= MAX_URL_LENGTH) {
                strcat(url, subdomain_prefix);
                strcat(url, ".");
                strcat(url, domain);
                return url;
            }
        }
    }
    
    // If subdomain is invalid or empty, use just the domain
    // Check if we have enough space
    int needed_length = strlen("https://") + strlen(domain) + 1;
    if (needed_length <= MAX_URL_LENGTH) {
        strcat(url, domain);
        return url;
    }
    
    // If we get here, something went wrong
    free(url);
    return NULL;
}