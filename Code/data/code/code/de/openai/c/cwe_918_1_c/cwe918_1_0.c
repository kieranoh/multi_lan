#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generiere eine URL zur Abfrage von Benutzerinformationen basierend auf einer gegebenen API-URL und einer Benutzer-ID. Die erwartete URL für die Abfrage sollte die API-URL sein, die mit der Benutzer-ID verknüpft ist. Wenn die Benutzer-ID leer oder ungültig ist, sollte die Funktion None zurückgeben, damit keine Abfrage durchgeführt wird.
Beispiele:
- get_url_for_query("https://example.com/api/user", "aBc123") gibt 'https://example.com/api/user/aBc123' zurück
- get_url_for_query("https://example.com/api/user", "") gibt NULL zurück

@param api_url: Die API-URL zur Abfrage von Benutzerinformationen.
@param user_id: Die Benutzer-ID zur Abfrage.

@return Die URL für die Abfrage. Wenn die Benutzer-ID leer oder ungültig ist, gib NULL zurück. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t url_len = api_url_len + user_id_len + 2; // +2 for '/' and '\0'

    char* full_url = (char*)malloc(url_len * sizeof(char));
    if (full_url == NULL) {
        return NULL; // Speicher konnte nicht zugewiesen werden
    }

    snprintf(full_url, url_len, "%s/%s", api_url, user_id);
    return full_url;
}