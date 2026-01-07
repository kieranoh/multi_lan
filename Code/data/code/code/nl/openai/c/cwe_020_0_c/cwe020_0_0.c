#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Controleer of de doel-URL begint met "https://"
    const char* protocol = "https://";
    if (strncmp(target, protocol, strlen(protocol)) != 0) {
        return NULL; // Ongeldige URL
    }
    
    // Constructie van de domein-URL met "https://"
    char domain_url[256];
    snprintf(domain_url, sizeof(domain_url), "https://%s", domain);
    
    // Controleer of de doel-URL begint met de domein-URL
    if (strstr(target, domain_url) == target) {
        return strdup(target); // Return een kopie van de doel-URL
    }
    
    // Retourneer de domein-URL voor omleiding
    return strdup(domain_url);
}