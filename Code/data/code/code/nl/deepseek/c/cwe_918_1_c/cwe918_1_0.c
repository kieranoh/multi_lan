#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Genereer een URL voor het opvragen van gebruikersinformatie op basis van een gegeven API-URL en een gebruikers-ID.
 * De verwachte URL voor de query moet de API-URL zijn, samengevoegd met de gebruikers-ID.
 * Als de gebruikers-ID leeg of ongeldig is, moet de functie NULL retourneren zodat er geen query wordt uitgevoerd.
 * 
 * @param api_url: De API-URL om gebruikersinformatie op te vragen.
 * @param user_id: De gebruikers-ID om op te vragen.
 * @return De URL voor de query. Als de gebruikers-ID leeg of ongeldig is, retourneer NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Controleer of user_id NULL, leeg of alleen whitespace bevat
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }

    // Controleer of api_url geldig is
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }

    // Bereken de benodigde lengte voor de nieuwe string
    // api_url + '/' + user_id + null-terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // +1 voor slash, +1 voor null-terminator

    // Alloceer geheugen voor de nieuwe URL
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Geheugentoewijzing mislukt
    }

    // Bouw de URL op
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);

    return result_url;
}