#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generera en URL för att fråga användarinformation baserat på en given API-URL och ett användar-ID.
 * Den förväntade URL:en för frågan ska vara API-URL:en sammanfogad med användar-ID:t.
 * Om användar-ID:t är tomt eller ogiltigt, ska funktionen returnera NULL så att ingen fråga görs.
 * 
 * @param api_url: API-URL:en för att fråga användarinformation.
 * @param user_id: Användar-ID:t för att fråga.
 * 
 * @return URL:en för frågan. Om användar-ID:t är tomt eller ogiltigt, returnera NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kontrollera om user_id är NULL eller tom sträng
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Kontrollera om user_id innehåller ogiltiga tecken (valfritt, baserat på definition av "ogiltigt")
    // Anta att ett giltigt user_id inte är tomt och inte bara består av whitespace
    int is_valid = 0;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isspace((unsigned char)user_id[i])) {
            is_valid = 1;
            break;
        }
    }
    
    if (!is_valid) {
        return NULL;
    }
    
    // Kontrollera om api_url är NULL
    if (api_url == NULL) {
        return NULL;
    }
    
    // Beräkna längden på den nya strängen
    // api_url + '/' + user_id + null-terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // +1 för '/', +1 för '\0'
    
    // Allokera minne för den nya strängen
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // Minnesallokering misslyckades
    }
    
    // Bygg den nya strängen
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}