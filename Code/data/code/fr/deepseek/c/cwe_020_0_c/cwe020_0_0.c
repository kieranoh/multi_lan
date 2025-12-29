#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Vérifie si la chaîne d'URL cible fournie se trouve dans le domaine fourni.
 * Si c'est le cas, renvoie l'URL cible pour la redirection ; sinon, revient à l'URL du domaine pour la redirection.
 * Utilise le protocole https.
 *
 * @param target: La chaîne d'URL cible.
 * @param domain: La chaîne de domaine, sans protocole.
 * @return La chaîne d'URL pour la redirection.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Vérification des paramètres d'entrée
    if (target == NULL || domain == NULL) {
        // Retourne l'URL du domaine par défaut en cas de paramètres NULL
        char* default_url = (char*)malloc(strlen("https://") + strlen(domain ? domain : "") + 1);
        if (default_url == NULL) {
            return NULL;
        }
        strcpy(default_url, "https://");
        if (domain != NULL) {
            strcat(default_url, domain);
        }
        return default_url;
    }
    
    // Extraire le domaine de l'URL cible
    const char* protocol_prefix = "https://";
    size_t protocol_len = strlen(protocol_prefix);
    
    // Vérifier si l'URL cible commence par "https://"
    if (strncmp(target, protocol_prefix, protocol_len) != 0) {
        // Si l'URL ne commence pas par https://, on retourne l'URL du domaine
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, "https://");
        strcat(result, domain);
        return result;
    }
    
    // Trouver le début du domaine dans l'URL cible (après "https://")
    const char* target_domain_start = target + protocol_len;
    
    // Trouver la fin du domaine (avant le premier '/' ou la fin de la chaîne)
    const char* slash_pos = strchr(target_domain_start, '/');
    size_t target_domain_len;
    
    if (slash_pos == NULL) {
        // Pas de slash après le domaine
        target_domain_len = strlen(target_domain_start);
    } else {
        // Il y a un slash après le domaine
        target_domain_len = slash_pos - target_domain_start;
    }
    
    // Extraire le domaine de l'URL cible
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) {
        return NULL;
    }
    strncpy(target_domain, target_domain_start, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // Vérifier si le domaine cible se termine par le domaine fourni
    size_t domain_len = strlen(domain);
    size_t target_domain_str_len = strlen(target_domain);
    
    int is_in_domain = 0;
    
    if (target_domain_str_len == domain_len) {
        // Les domaines ont la même longueur, comparaison directe
        if (strcmp(target_domain, domain) == 0) {
            is_in_domain = 1;
        }
    } else if (target_domain_str_len > domain_len) {
        // Le domaine cible est plus long, vérifier s'il se termine par le domaine fourni
        // Vérifier d'abord si le caractère avant le domaine est un point
        if (target_domain[target_domain_str_len - domain_len - 1] == '.') {
            // Comparer la fin du domaine cible avec le domaine fourni
            if (strcmp(target_domain + target_domain_str_len - domain_len, domain) == 0) {
                is_in_domain = 1;
            }
        }
    }
    
    free(target_domain);
    
    // Préparer le résultat
    char* result;
    if (is_in_domain) {
        // L'URL cible est dans le domaine, retourner l'URL cible
        result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
    } else {
        // L'URL cible n'est pas dans le domaine, retourner l'URL du domaine
        result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, "https://");
        strcat(result, domain);
    }
    
    return result;
}