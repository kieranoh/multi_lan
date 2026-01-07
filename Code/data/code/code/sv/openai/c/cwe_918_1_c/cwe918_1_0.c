#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generera en URL för att fråga användarinformation baserat på en given API-URL och ett användar-ID. Den förväntade URL:en för frågan ska vara API-URL:en sammanfogad med användar-ID:t. Om användar-ID:t är tomt eller ogiltigt, ska funktionen returnera None så att ingen fråga görs.
Exempel:
- get_url_for_query("https://example.com/api/user", "aBc123") returnerar 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") returnerar NULL

@param api_url: API-URL:en för att fråga användarinformation.
@param user_id: Användar-ID:t för att fråga.

@return URL:en för frågan. Om användar-ID:t är tomt eller ogiltigt, returnera NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kontrollera om user_id är NULL eller tomt
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Beräkna längden på den nya URL:en
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t total_length = api_url_length + user_id_length + 2; // +1 för '/' och +1 för '\0'

    // Allokera minne för den nya URL:en
    char* query_url = (char*)malloc(total_length * sizeof(char));
    if (query_url == NULL) {
        return NULL; // Returnera NULL om minnesallokeringen misslyckas
    }

    // Skapa den nya URL:en
    sprintf(query_url, "%s/%s", api_url, user_id);

    return query_url; // Återvänd den skapade URL:en
}