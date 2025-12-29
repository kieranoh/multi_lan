#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256

bool is_valid_subdomain(const char* subdomain) {
    if (subdomain == NULL || *subdomain == '\0') {
        return false;
    }

    // Sprawdź, czy subdomena zawiera niedozwolone znaki
    for (const char *p = subdomain; *p != '\0'; p++) {
        if (!((*p >= 'a' && *p <= 'z') || 
               (*p >= 'A' && *p <= 'Z') || 
               (*p >= '0' && *p <= '9') || 
               *p == '-' || *p == '.')) {
            return false;
        }
    }
    
    return true;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    
    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, sizeof(url), "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, sizeof(url), "https://%s", domain);
    }

    return url;
}