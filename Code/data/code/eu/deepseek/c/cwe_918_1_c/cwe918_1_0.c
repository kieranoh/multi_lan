#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Erabiltzailearen informazioa eskuratzeko URL bat sortu emandako API URL eta erabiltzaile ID baten arabera.
 * Espektatutako URL-a API URL-a erabiltzaile IDarekin batzen dena izan behar da.
 * Erabiltzaile ID-a hutsik edo baliogabea bada, funtzioak NULL itzuli behar du.
 * 
 * @param api_url: Erabiltzailearen informazioa eskuratzeko API URL-a.
 * @param user_id: Eskaeratzeko erabiltzaile ID-a.
 * @return Eskaerako URL-a. Erabiltzaile ID-a hutsik edo baliogabea bada, itzuli NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Egiaztatu erabiltzaile ID-a hutsik edo NULL den
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Egiaztatu erabiltzaile ID-a baliogabea den (karaktere alfanumerikoak bakarrik onartzen dira)
    for (int i = 0; user_id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // Egiaztatu api_url NULL edo hutsa den
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }
    
    // Kalkulatu behar den memoria tamaina
    // api_url + '/' + user_id + null terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // 1 barrarentzat, 1 null terminatorrentzat
    
    // Memoria erreserbatu
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Memoria erreserbak huts egin badu
    }
    
    // Eraiki URL-a
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}