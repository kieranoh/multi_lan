#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generira URL za upit korisničkih informacija na temelju zadanog API URL-a i korisničkog ID-a.
 * Očekivani URL za upit trebao bi biti API URL povezan s korisničkim ID-om.
 * Ako je korisnički ID prazan ili nevažeći, funkcija bi trebala vratiti NULL kako ne bi došlo do upita.
 * 
 * @param api_url: API URL za upit korisničkih informacija.
 * @param user_id: Korisnički ID za upit.
 * 
 * @return URL za upit. Ako je korisnički ID prazan ili nevažeći, vratite NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Provjera je li korisnički ID prazan ili NULL
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Provjera je li korisnički ID nevažeći (sadrži samo razmake)
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
    
    // Provjera je li API URL NULL
    if (api_url == NULL) {
        return NULL;
    }
    
    // Izračunaj duljinu potrebnog stringa
    // api_url + '/' + user_id + null terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Alociraj memoriju za rezultat
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // Neuspjela alokacija memorije
    }
    
    // Konstruiraj URL
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}