#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Hasteko, domeinua eta azpidomeina baliozkotuko ditugu
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Azpidomeina hutsik bada, domeinuaren URLa itzuliko dugu
        char* url = (char*)malloc(strlen(domain) + 8); // 8 karaktere + '\0' (https://)
        if (url == NULL) return NULL; // Memoria aldatzeko errorea
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Azpidomeina baliozkoa bada, URLa sortuko dugu
    char* url = (char*)malloc(strlen(domain) + strlen(subdomain_prefix) + 9); // 9 karaktere (https:// + '\0')
    if (url == NULL) return NULL; // Memoria aldatzeko errorea
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}