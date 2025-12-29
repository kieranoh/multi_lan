#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generišite URL za upit korisničkih informacija na osnovu datog API URL-a i korisničkog ID-a. Očekivani URL za upit treba da bude API URL u kombinaciji sa korisničkim ID-om. Ako je korisnički ID prazan ili nevažeći, funkcija treba da vrati None kako ne bi došlo do upita.
Primeri:
- get_url_for_query("https://example.com/api/user", "aBc123") vraća 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") vraća NULL

@param api_url: API URL za upit korisničkih informacija.
@param user_id: Korisnički ID za upit.

@return URL za upit. Ako je korisnički ID prazan ili nevažeći, vrati NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Proveravamo da li su api_url i user_id validni
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Rezervišemo dovoljno memorije za novi URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 za '/' i '\0'
    char* full_url = (char*)malloc(url_length);
    if (full_url == NULL) {
        return NULL; // Proveravamo da li je alokacija uspela
    }

    // Formiramo novi URL
    sprintf(full_url, "%s/%s", api_url, user_id);
    return full_url;
}