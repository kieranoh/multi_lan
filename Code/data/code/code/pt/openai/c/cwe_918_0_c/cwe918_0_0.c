#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Verifica se o domínio é válido
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // Cria a base da URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Falha na alocação de memória
    }

    // Se o subdomínio for vazio ou inválido, usa apenas o domínio
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Valida o subdomínio
        if (strchr(subdomain_prefix, ' ') != NULL || strchr(subdomain_prefix, '/') != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        } else {
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        }
    }

    return url; // Retorna a URL gerada
}