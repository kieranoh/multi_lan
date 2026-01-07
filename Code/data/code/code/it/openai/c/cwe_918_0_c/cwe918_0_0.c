#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Controlla se il dominio è nullo o vuoto
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Se il prefisso del sottodominio è nullo o vuoto, restituiamo solo il dominio
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*) malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Calcola la lunghezza dell'URL finale
    int url_length = strlen("https://") + strlen(subdomain_prefix) + strlen(domain) + 2; // +2 per il punto e la terminazione di stringa
    if (url_length >= MAX_URL_LENGTH) {
        return NULL; // URL troppo lungo
    }

    // Alloca memoria per l'URL
    char* url = (char*) malloc(url_length);
    if (url != NULL) {
        snprintf(url, url_length, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}