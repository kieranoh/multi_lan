#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kontrola platnosti vstupů
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Vypočítání délky nové URL
    size_t new_url_length = strlen(api_url) + strlen(user_id) + 2; // +2 pro '/' a '\0'

    // Alokace paměti pro novou URL
    char* new_url = (char*)malloc(new_url_length);
    if (new_url == NULL) {
        return NULL; // Kontrola úspěšnosti alokace
    }

    // Sestavení nové URL
    snprintf(new_url, new_url_length, "%s/%s", api_url, user_id);

    return new_url; // Vrátí nově vytvořenou URL
}