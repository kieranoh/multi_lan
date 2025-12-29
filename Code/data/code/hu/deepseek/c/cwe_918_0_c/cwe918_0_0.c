#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    url[0] = '\0';
    
    if (domain == NULL) {
        return url;
    }
    
    // Ellenőrizzük, hogy az aldomain érvényes-e (nem NULL és nem üres string)
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Ellenőrizzük, hogy az aldomain csak érvényes karaktereket tartalmaz-e
        // (betűk, számok, pontok és kötőjelek)
        int valid = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!((c >= 'a' && c <= 'z') || 
                  (c >= 'A' && c <= 'Z') || 
                  (c >= '0' && c <= '9') || 
                  c == '.' || c == '-')) {
                valid = 0;
                break;
            }
        }
        has_valid_subdomain = valid;
    }
    
    // URL összeállítása
    if (has_valid_subdomain) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}