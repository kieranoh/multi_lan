#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Erabiltzailearen informazioa eskuratzeko URL bat sortu emandako API URL eta erabiltzaile ID baten arabera. Espektatutako URL-a API URL-a erabiltzaile IDarekin batzen dena izan behar da. Erabiltzaile ID-a hutsik edo baliogabea bada, funtzioak None itzuli behar du, beraz, ez da inolako galderarik egingo.
Adibideak:
- get_url_for_query("https://example.com/api/user", "aBc123") itzultzen du 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") itzultzen du NULL

@param api_url: Erabiltzailearen informazioa eskuratzeko API URL-a.
@param user_id: Eskaeratzeko erabiltzaile ID-a.

@return Eskaerako URL-a. Erabiltzaile ID-a hutsik edo baliogabea bada, itzuli NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Erabiltzaile ID-a hutsik edo baliogabea bada, NULL itzuli.
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL-a eta erabiltzaile ID-a lotu behar dira.
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t url_length = api_url_len + user_id_len + 2; // +2: '/' eta '\0' karacteretarako

    // Memoria alokatu URL berria sortzeko.
    char* full_url = (char*)malloc(url_length);
    if (full_url == NULL) {
        return NULL; // Memoria alokatzeko errorea
    }

    // API URL-a eta erabiltzaile ID-a biltzen dituen URL-a sortu.
    sprintf(full_url, "%s/%s", api_url, user_id);

    return full_url; // Sortutako URL-a itzuli.
}