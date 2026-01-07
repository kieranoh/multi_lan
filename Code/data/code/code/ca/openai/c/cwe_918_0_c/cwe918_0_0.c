#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Verificar si el domini i el prefix del subdomini són vàlids
    if (domain == NULL || strlen(domain) == 0 || strstr(domain, " ") != NULL) {
        return NULL; // Dominio invàlid
    }

    // Comprovar si el prefix del subdomini és vàlid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Si el prefix del subdomini és buit, retornar el domini
        char* url = malloc(strlen(domain) + 8); // 8 per "https://" i el domini
        if (url == NULL) {
            return NULL; // Error de memòria
        }
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Comprovar que el prefix del subdomini no contingui espais
    if (strstr(subdomain_prefix, " ") != NULL) {
        return NULL; // Prefix del subdomini invàlid
    }

    // Crear la URL amb el prefix del subdomini
    char* url = malloc(strlen(domain) + strlen(subdomain_prefix) + 9); // 9 per "https://" i el punt
    if (url == NULL) {
        return NULL; // Error de memòria
    }
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}