#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Costruisci l'URL del dominio con il protocollo https
    char* domain_url = (char*)malloc(strlen(domain) + 9); // 8 per "https://" + 1 per '\0'
    if (domain_url == NULL) {
        return NULL; // Gestione dell'errore di allocazione
    }
    sprintf(domain_url, "https://%s", domain);

    // Controlla se l'URL di destinazione inizia con il dominio
    if (strstr(target, domain_url) == target) {
        // Se il target è nello stesso dominio, restituisci il target
        free(domain_url);
        return strdup(target); // Duplica la stringa target per restituirla
    }

    // Altrimenti, restituisci l'URL del dominio
    free(domain_url);
    return domain_url; // Restituisce il dominio come URL
}