#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Genera un URL per interrogare le informazioni dell'utente basato su un dato URL API e un ID utente.
 * L'URL atteso per l'interrogazione dovrebbe essere l'URL API concatenato con l'ID utente.
 * Se l'ID utente è vuoto o non valido, la funzione dovrebbe restituire NULL in modo che non venga effettuata alcuna interrogazione.
 * 
 * @param api_url: L'URL API per interrogare le informazioni dell'utente.
 * @param user_id: L'ID utente da interrogare.
 * 
 * @return L'URL per l'interrogazione. Se l'ID utente è vuoto o non valido, restituisci NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Controlla se l'ID utente è NULL o vuoto
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Controlla se l'ID utente contiene solo caratteri alfanumerici
    // (questa è una definizione di validità comune per gli ID)
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // Controlla se l'URL API è NULL o vuoto
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }
    
    // Calcola la lunghezza necessaria per la stringa risultante
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // +1 per '/' e +1 per '\0'
    
    // Alloca memoria per l'URL risultante
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Fallimento nell'allocazione della memoria
    }
    
    // Costruisce l'URL risultante
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}