#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define HTTPS_PREFIX "https://"

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Überprüfen, ob die Domain leer ist
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // Überprüfen, ob die Subdomain leer ist oder ungültige Zeichen enthält
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Wenn Subdomain leer ist, zurück zur Domain
        char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(domain) + 1);
        if (url == NULL) {
            return NULL; // Speicherfehler
        }
        sprintf(url, "%s%s", HTTPS_PREFIX, domain);
        return url;
    }

    // Überprüfen, ob die Subdomain ungültige Zeichen enthält (z.B. Punkt am Anfang oder Ende)
    if (subdomain_prefix[0] == '.' || subdomain_prefix[strlen(subdomain_prefix) - 1] == '.') {
        return get_url_to_visit(domain, NULL); // Ungültige Subdomain, zurück zur Domain
    }

    // Erstellen der vollständigen URL
    char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(subdomain_prefix) + strlen(domain) + 2);
    if (url == NULL) {
        return NULL; // Speicherfehler
    }
    sprintf(url, "%s%s.%s", HTTPS_PREFIX, subdomain_prefix, domain);
    return url;
}