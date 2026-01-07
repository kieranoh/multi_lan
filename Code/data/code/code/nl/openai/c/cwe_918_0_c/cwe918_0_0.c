#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Controleer of het domein en het subdomein geldig zijn
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Als het subdomein leeg is, retourneer dan alleen het domein
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc((strlen(domain) + 8) * sizeof(char)); // 8 is voor "https://"
        if (url != NULL) {
            snprintf(url, (strlen(domain) + 8), "https://%s", domain);
        }
        return url;
    }

    // Controleer of het subdomein geldig is (geen ongeldige karakters)
    if (strchr(subdomain_prefix, ' ') != NULL || strchr(subdomain_prefix, '/') != NULL) {
        return NULL;
    }

    // Bereken de lengte van de volledige URL
    size_t url_length = strlen(domain) + strlen(subdomain_prefix) + 9; // 9 is voor "https://" en een punt
    char* url = (char*)malloc(url_length * sizeof(char));
    if (url != NULL) {
        snprintf(url, url_length, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}