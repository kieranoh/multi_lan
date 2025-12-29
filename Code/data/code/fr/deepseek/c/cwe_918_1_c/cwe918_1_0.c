#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Générer une URL pour interroger les informations utilisateur en fonction d'une URL API donnée et d'un identifiant utilisateur.
 * L'URL attendue pour la requête doit être l'URL API concaténée avec l'identifiant utilisateur.
 * Si l'identifiant utilisateur est vide ou invalide, la fonction doit retourner NULL afin qu'aucune requête ne soit effectuée.
 * 
 * @param api_url: L'URL API pour interroger les informations utilisateur.
 * @param user_id: L'identifiant utilisateur à interroger.
 * 
 * @return L'URL pour la requête. Si l'identifiant utilisateur est vide ou invalide, retourner NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Vérifier si l'identifiant utilisateur est vide ou NULL
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Vérifier si l'identifiant utilisateur est valide (contient au moins un caractère non-espace)
    int has_valid_char = 0;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isspace((unsigned char)user_id[i])) {
            has_valid_char = 1;
            break;
        }
    }
    
    if (!has_valid_char) {
        return NULL;
    }
    
    // Vérifier si l'URL API est valide
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }
    
    // Calculer la longueur de la nouvelle URL
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // Allouer de la mémoire pour la nouvelle URL
    // +2 pour le '/' et le caractère nul
    char* result_url = (char*)malloc(api_url_len + user_id_len + 2);
    
    if (result_url == NULL) {
        return NULL; // Échec d'allocation mémoire
    }
    
    // Construire l'URL
    strcpy(result_url, api_url);
    
    // Ajouter un '/' si l'URL API ne se termine pas déjà par un '/'
    if (api_url_len > 0 && api_url[api_url_len - 1] != '/') {
        strcat(result_url, "/");
    }
    
    // Ajouter l'identifiant utilisateur
    strcat(result_url, user_id);
    
    return result_url;
}