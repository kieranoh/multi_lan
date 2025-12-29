#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    
    // Tarkistetaan, onko aliverkkotunnus tyhjää tai virheellistä
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0 || strchr(subdomain_prefix, '.') != NULL) {
        // Palautetaan vain verkkotunnus HTTPS-protokollalla
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Luodaan url aliverkkotunnuksella
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}