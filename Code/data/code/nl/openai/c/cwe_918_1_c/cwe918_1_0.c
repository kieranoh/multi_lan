#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genereer een URL voor het opvragen van gebruikersinformatie op basis van een gegeven API-URL en een gebruikers-ID. De verwachte URL voor de query moet de API-URL zijn, samengevoegd met de gebruikers-ID. Als de gebruikers-ID leeg of ongeldig is, moet de functie None retourneren zodat er geen query wordt uitgevoerd.
Voorbeelden:
- get_url_for_query("https://example.com/api/user", "aBc123") retourneert 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") retourneert NULL

@param api_url: De API-URL om gebruikersinformatie op te vragen.
@param user_id: De gebruikers-ID om op te vragen.

@return De URL voor de query. Als de gebruikers-ID leeg of ongeldig is, retourneer NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t url_length = api_url_length + user_id_length + 2; // 1 for '/' and 1 for '\0'

    char* query_url = (char*)malloc(url_length);
    if (query_url == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    snprintf(query_url, url_length, "%s/%s", api_url, user_id);
    return query_url;
}