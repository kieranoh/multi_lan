#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Kontrola vstupních parametrů
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // Kontrola, zda je user_id prázdný řetězec
    if (strlen(user_id) == 0) {
        return NULL;
    }
    
    // Kontrola, zda user_id obsahuje pouze platné znaky (písmena, číslice, případně podtržítko)
    // Můžeme definovat, co považujeme za "neplatné" - například prázdné nebo obsahující pouze mezery
    int valid = 0;
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isspace((unsigned char)user_id[i])) {
            valid = 1;
            break;
        }
    }
    
    if (!valid) {
        return NULL;
    }
    
    // Alokace paměti pro výsledné URL
    // Délka = api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    char* result = (char*)malloc(api_url_len + user_id_len + 2); // +2 pro '/' a '\0'
    
    if (result == NULL) {
        return NULL; // Chyba alokace paměti
    }
    
    // Sestavení výsledného URL
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}