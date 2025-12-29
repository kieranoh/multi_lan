#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Montando a URL do domínio com o protocolo https
    char domain_url[256];
    snprintf(domain_url, sizeof(domain_url), "https://%s", domain);

    // Verificando se a URL de destino começa com o domínio
    if (strstr(target, domain_url) == target) {
        // Se sim, retorne a URL de destino
        return strdup(target);
    } else {
        // Caso contrário, retorne a URL do domínio
        return strdup(domain_url);
    }
}