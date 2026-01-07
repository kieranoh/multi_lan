#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Überprüfen, ob die Subdomain leer oder ungültig ist
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0') {
        // Wenn ja, geben wir nur die Domain zurück
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Generieren der vollständigen URL mit der Subdomain
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}