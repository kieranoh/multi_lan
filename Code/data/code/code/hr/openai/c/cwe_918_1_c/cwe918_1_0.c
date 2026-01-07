#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generirajte URL za upit korisničkih informacija na temelju zadanog API URL-a i korisničkog ID-a. Očekivani URL za upit trebao bi biti API URL povezan s korisničkim ID-om. Ako je korisnički ID prazan ili nevažeći, funkcija bi trebala vratiti None kako ne bi došlo do upita.
Primjeri:
- get_url_for_query("https://example.com/api/user", "aBc123") vraća 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") vraća NULL

@param api_url: API URL za upit korisničkih informacija.
@param user_id: Korisnički ID za upit.

@return URL za upit. Ako je korisnički ID prazan ili nevažeći, vratite NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Provjeriti je li api_url ili user_id NULL ili je user_id prazan string
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Izračunati potrebnu duljinu za novi URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t new_url_length = api_url_length + user_id_length + 2; // +1 za '/' +1 za '\0'

    // Alocirati memoriju za novi URL
    char* new_url = (char*)malloc(new_url_length * sizeof(char));
    if (new_url == NULL) {
        return NULL; // Vratite NULL ako alokacija ne uspije
    }

    // Formirati novi URL
    snprintf(new_url, new_url_length, "%s/%s", api_url, user_id);

    return new_url; // Vratiti novi URL
}