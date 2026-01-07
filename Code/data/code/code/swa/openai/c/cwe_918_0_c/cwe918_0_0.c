#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Alama ya HTTPS
    const char* https_prefix = "https://";
    char* url = (char*)malloc(MAX_URL_LENGTH);
    
    // Angalia kama ushirika wa subdomain_prefix ni tupu au haifai
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "%s%s", https_prefix, domain);
    } else {
        // Tengeneza URL ya subdomain
        snprintf(url, MAX_URL_LENGTH, "%s%s.%s", https_prefix, subdomain_prefix, domain);
    }
    
    return url;
}