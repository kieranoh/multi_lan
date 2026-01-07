#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allocate memory for the result URL
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Initialize result string
    result[0] = '\0';
    
    // Check if domain is NULL or empty
    if (domain == NULL || domain[0] == '\0') {
        strcpy(result, "https://");
        return result;
    }
    
    // Validate subdomain prefix
    int valid_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Check if subdomain contains only valid characters (alphanumeric, dots, hyphens)
        valid_subdomain = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                valid_subdomain = 0;
                break;
            }
        }
        
        // Ensure subdomain doesn't start or end with dot or hyphen
        if (valid_subdomain) {
            int len = strlen(subdomain_prefix);
            if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                subdomain_prefix[len-1] == '.' || subdomain_prefix[len-1] == '-') {
                valid_subdomain = 0;
            }
        }
    }
    
    // Build the URL
    strcpy(result, "https://");
    
    if (valid_subdomain) {
        // Append subdomain prefix
        strcat(result, subdomain_prefix);
        strcat(result, ".");
    }
    
    // Append domain
    strcat(result, domain);
    
    // Ensure we don't exceed MAX_URL_LENGTH
    if (strlen(result) >= MAX_URL_LENGTH) {
        result[MAX_URL_LENGTH - 1] = '\0';
    }
    
    return result;
}