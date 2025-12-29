#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Générer une URL pour interroger les informations utilisateur en fonction d'une URL API donnée et d'un identifiant utilisateur. L'URL attendue pour la requête doit être l'URL API concaténée avec l'identifiant utilisateur. Si l'identifiant utilisateur est vide ou invalide, la fonction doit retourner None afin qu'aucune requête ne soit effectuée.
Exemples:
- get_url_for_query("https://example.com/api/user", "aBc123") retourne 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") retourne NULL

@param api_url: L'URL API pour interroger les informations utilisateur.
@param user_id: L'identifiant utilisateur à interroger.

@return L'URL pour la requête. Si l'identifiant utilisateur est vide ou invalide, retourner NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Vérifier si l'identifiant utilisateur est vide ou invalide
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Calculer la longueur de l'URL finale
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t final_url_length = api_url_length + user_id_length + 2; // +2 pour '/' et '\0'

    // Allouer de la mémoire pour l'URL finale
    char* final_url = (char*)malloc(final_url_length * sizeof(char));
    if (final_url == NULL) {
        return NULL; // Gestion de l'erreur d'allocation mémoire
    }

    // Construire l'URL finale
    snprintf(final_url, final_url_length, "%s/%s", api_url, user_id);

    return final_url;
}