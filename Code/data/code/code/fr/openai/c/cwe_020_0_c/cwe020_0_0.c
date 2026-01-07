#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Vérifie si l'URL cible commence par le protocole https://
    if (strncmp(target, "https://", 8) != 0) {
        return NULL; // Retourne NULL si l'URL n'est pas valide
    }
    
    // Vérifie si le domaine est présent dans l'URL cible
    const char* pos = strstr(target, domain);
    if (pos != NULL && (pos == target + 8 || *(pos - 1) == '.' || *(pos - 1) == '/')) {
        // Si le domaine est trouvé et qu'il est bien formé, renvoie l'URL cible
        return strdup(target);
    } else {
        // Sinon, construit l'URL de redirection vers le domaine donné
        char* redirect_url = malloc(strlen(domain) + 9); // 9 pour "https://" et '\0'
        if (redirect_url == NULL) {
            return NULL; // Retourne NULL si l'allocation échoue
        }
        sprintf(redirect_url, "https://%s", domain);
        return redirect_url;
    }
}