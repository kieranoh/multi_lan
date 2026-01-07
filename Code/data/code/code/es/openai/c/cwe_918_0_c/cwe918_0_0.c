#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Verificar si el dominio es nulo o vacío
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // Validar el subdominio
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Si el subdominio está vacío, retornar solo el dominio con HTTPS
        char* url = (char*)malloc(MAX_URL_LENGTH);
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        return url;
    }

    // Verificar si el subdominio es válido (puede contener letras, números, y puntos)
    for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
        if (!((subdomain_prefix[i] >= 'a' && subdomain_prefix[i] <= 'z') ||
              (subdomain_prefix[i] >= 'A' && subdomain_prefix[i] <= 'Z') ||
              (subdomain_prefix[i] >= '0' && subdomain_prefix[i] <= '9') ||
              subdomain_prefix[i] == '.')) {
            // Si hay un carácter inválido, retornar solo el dominio con HTTPS
            char* url = (char*)malloc(MAX_URL_LENGTH);
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
            return url;
        }
    }

    // Construir la URL final con el subdominio
    char* url = (char*)malloc(MAX_URL_LENGTH);
    snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    return url;
}