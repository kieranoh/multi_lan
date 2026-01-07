#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Provera da li je user_id NULL ili prazan string
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Provera da li user_id sadrži samo alfanumeričke karaktere
    // (može se prilagoditi specifičnim zahtevima za ID format)
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // Izračunavanje dužine rezultujućeg stringa
    // api_url + '/' + user_id + null terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Alokacija memorije za rezultujući URL
    char* result_url = (char*)malloc(total_len);
    if (result_url == NULL) {
        return NULL; // Neuspešna alokacija memorije
    }
    
    // Konstruisanje URL-a
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}