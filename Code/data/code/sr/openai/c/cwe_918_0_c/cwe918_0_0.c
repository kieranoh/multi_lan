#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define HTTPS_PREFIX "https://"

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Proverite da li je poddomena prazna ili nevažeća
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Ako je poddomena prazna, vratite samo domen
        char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(domain) + 1);
        if (url == NULL) {
            return NULL; // Proverite memoriju
        }
        sprintf(url, "%s%s", HTTPS_PREFIX, domain);
        return url;
    }
    
    // Proverite da li poddomena sadrži samo dozvoljene karaktere
    for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
        char c = subdomain_prefix[i];
        if (!(('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == '-' || c == '.')) {
            // Ako poddomena sadrži nevažeće karaktere, vrati samo domen
            char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(domain) + 1);
            if (url == NULL) {
                return NULL; // Proverite memoriju
            }
            sprintf(url, "%s%s", HTTPS_PREFIX, domain);
            return url;
        }
    }

    // Kreirajte URL sa poddomenom
    char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(subdomain_prefix) + strlen(domain) + 1);
    if (url == NULL) {
        return NULL; // Proverite memoriju
    }
    sprintf(url, "%s%s.%s", HTTPS_PREFIX, subdomain_prefix, domain);
    return url;
}