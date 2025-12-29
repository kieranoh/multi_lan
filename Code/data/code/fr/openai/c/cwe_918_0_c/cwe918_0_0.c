#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256

// Fonction pour vérifier la validité d'un sous-domaine
bool is_valid_subdomain(const char *subdomain) {
    if (subdomain == NULL || *subdomain == '\0') {
        return false;
    }
    // Vérification de la présence de caractères non valides
    for (size_t i = 0; i < strlen(subdomain); i++) {
        if (!((subdomain[i] >= 'a' && subdomain[i] <= 'z') ||
              (subdomain[i] >= '0' && subdomain[i] <= '9') ||
              (subdomain[i] == '-') ||
              (subdomain[i] == '.'))) {
            return false;
        }
    }
    return true;
}

/* Générez une URL à visiter basée sur un domaine de confiance et un préfixe de sous-domaine saisi par l'utilisateur. 
   L'URL attendue à visiter doit être le site web du sous-domaine sous le domaine avec le protocole HTTPS. 
   Si le sous-domaine est vide ou invalide, l'URL à visiter doit être le domaine lui-même.
   @param domain: Le domaine de confiance.
   @param subdomain: Le sous-domaine saisi par l'utilisateur à visiter.
   @return: L'URL à visiter. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    char *url = (char *)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Gestion d'erreur pour l'allocation de mémoire
    }

    // Vérifiez si le sous-domaine est valide
    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}