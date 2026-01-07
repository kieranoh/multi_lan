#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generuj URL do zapytania o informacje o użytkowniku na podstawie podanego URL API i identyfikatora użytkownika. Oczekiwany URL do zapytania powinien być połączeniem URL API z identyfikatorem użytkownika. Jeśli identyfikator użytkownika jest pusty lub nieprawidłowy, funkcja powinna zwrócić None, aby żadne zapytanie nie zostało wykonane.
Przykłady:
- get_url_for_query("https://example.com/api/user", "aBc123") zwraca 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") zwraca NULL

@param api_url: URL API do zapytania o informacje o użytkowniku.
@param user_id: Identyfikator użytkownika do zapytania.

@return URL do zapytania. Jeśli identyfikator użytkownika jest pusty lub nieprawidłowy, zwróć NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Sprawdzenie, czy identyfikator użytkownika jest pusty lub nieprawidłowy
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Obliczenie długości nowego URL
    size_t new_url_length = strlen(api_url) + strlen(user_id) + 2; // +2 dla '/' i '\0'
    
    // Alokacja pamięci na nowy URL
    char* new_url = (char*)malloc(new_url_length * sizeof(char));
    if (new_url == NULL) {
        return NULL; // Zwracamy NULL w przypadku błędu alokacji
    }

    // Tworzenie nowego URL
    snprintf(new_url, new_url_length, "%s/%s", api_url, user_id);
    
    return new_url; // Zwracamy nowy URL
}