#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generuje URL do zapytania o informacje o użytkowniku na podstawie podanego URL API i identyfikatora użytkownika.
 * Oczekiwany URL do zapytania powinien być połączeniem URL API z identyfikatorem użytkownika.
 * Jeśli identyfikator użytkownika jest pusty lub nieprawidłowy, funkcja powinna zwrócić NULL.
 * 
 * @param api_url: URL API do zapytania o informacje o użytkowniku.
 * @param user_id: Identyfikator użytkownika do zapytania.
 * @return URL do zapytania. Jeśli identyfikator użytkownika jest pusty lub nieprawidłowy, zwróć NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Sprawdź czy user_id jest NULL lub pusty
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Sprawdź czy api_url jest NULL lub pusty
    if (api_url == NULL || strlen(api_url) == 0) {
        return NULL;
    }
    
    // Oblicz długość potrzebnego bufora
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Alokuj pamięć dla nowego stringa
    char* result_url = (char*)malloc(total_len);
    if (result_url == NULL) {
        return NULL; // Błąd alokacji pamięci
    }
    
    // Skopiuj api_url do result_url
    strcpy(result_url, api_url);
    
    // Dodaj '/' jeśli api_url nie kończy się na '/'
    if (api_url_len > 0 && api_url[api_url_len - 1] != '/') {
        strcat(result_url, "/");
    }
    
    // Dodaj user_id
    strcat(result_url, user_id);
    
    return result_url;
}