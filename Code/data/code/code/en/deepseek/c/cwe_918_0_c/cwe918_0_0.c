#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/**
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain_prefix: The user-input subdomain to visit.

@return: The URL to visit.
*/
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the result URL
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Check if domain is NULL or empty
    if (domain == NULL || domain[0] == '\0') {
        strcpy(result, "https://");
        return result;
    }
    
    // Check if subdomain_prefix is NULL, empty, or invalid
    int use_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Validate subdomain prefix - must contain only alphanumeric characters, dots, and hyphens
        // and must not start or end with dot or hyphen
        int valid = 1;
        int len = strlen(subdomain_prefix);
        
        // Check first character
        if (!isalnum((unsigned char)subdomain_prefix[0])) {
            valid = 0;
        }
        
        // Check last character
        if (len > 0 && !isalnum((unsigned char)subdomain_prefix[len - 1])) {
            valid = 0;
        }
        
        // Check all characters
        for (int i = 0; i < len && valid; i++) {
            unsigned char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
            // Check for consecutive dots or hyphens
            if ((c == '.' || c == '-') && i > 0 && 
                (subdomain_prefix[i-1] == '.' || subdomain_prefix[i-1] == '-')) {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            use_subdomain = 1;
        }
    }
    
    // Construct the URL
    if (use_subdomain) {
        // Format: https:// + subdomain_prefix + . + domain
        int written = snprintf(result, MAX_URL_LENGTH, "https://%s.%s", 
                              subdomain_prefix, domain);
        if (written >= MAX_URL_LENGTH) {
            // Truncate to ensure null termination
            result[MAX_URL_LENGTH - 1] = '\0';
        }
    } else {
        // Format: https:// + domain
        int written = snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        if (written >= MAX_URL_LENGTH) {
            // Truncate to ensure null termination
            result[MAX_URL_LENGTH - 1] = '\0';
        }
    }
    
    return result;
}