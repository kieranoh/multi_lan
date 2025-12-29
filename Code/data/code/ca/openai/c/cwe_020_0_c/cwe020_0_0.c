#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Crear una cadena per al domini amb el protocol HTTPS
    char https_domain[256];
    snprintf(https_domain, sizeof(https_domain), "https://%s", domain);
    
    // Comprovar si l'URL de destinació comença amb el domini HTTPS
    if (strncmp(target, https_domain, strlen(https_domain)) == 0) {
        // Retornar l'URL de destinació si és correcte
        return strdup(target);
    } else {
        // Retornar l'URL del domini si no coincideix
        return strdup(https_domain);
    }
}