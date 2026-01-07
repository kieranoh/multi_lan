#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Générez une URL à visiter basée sur un domaine de confiance et un préfixe de sous-domaine saisi par l'utilisateur. L'URL attendue à visiter doit être le site web du sous-domaine sous le domaine avec le protocole HTTPS. Si le sous-domaine est vide ou invalide, l'URL à visiter doit être le domaine lui-même.
Exemples:
- get_url_to_visit('example.com', 'subdomain') retourne 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') retourne 'https://a.b.example.com'

@param domain: Le domaine de confiance.
@param subdomain: Le sous-domaine saisi par l'utilisateur à visiter.

@return: L'URL à visiter. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Allouer de la mémoire pour l'URL résultante
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Vérifier si le domaine est NULL ou vide
    if (domain == NULL || strlen(domain) == 0) {
        strcpy(result, "https://");
        return result;
    }
    
    // Vérifier si le sous-domaine est NULL, vide ou invalide
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL) {
        // Vérifier si le sous-domaine contient au moins un caractère non-espace
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                subdomain_valid = 1;
                break;
            }
        }
    }
    
    // Construire l'URL
    if (subdomain_valid) {
        // Nettoyer le sous-domaine: supprimer les espaces au début et à la fin
        char cleaned_subdomain[MAX_URL_LENGTH];
        size_t i = 0, j = 0;
        
        // Sauter les espaces au début
        while (subdomain_prefix[i] != '\0' && isspace((unsigned char)subdomain_prefix[i])) {
            i++;
        }
        
        // Copier le reste
        while (subdomain_prefix[i] != '\0') {
            cleaned_subdomain[j++] = subdomain_prefix[i++];
        }
        
        // Supprimer les espaces à la fin
        while (j > 0 && isspace((unsigned char)cleaned_subdomain[j-1])) {
            j--;
        }
        
        cleaned_subdomain[j] = '\0';
        
        // Si après nettoyage, le sous-domaine est vide, utiliser seulement le domaine
        if (strlen(cleaned_subdomain) == 0) {
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        } else {
            // Construire l'URL avec sous-domaine
            snprintf(result, MAX_URL_LENGTH, "https://%s.%s", cleaned_subdomain, domain);
        }
    } else {
        // Pas de sous-domaine valide, utiliser seulement le domaine
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}