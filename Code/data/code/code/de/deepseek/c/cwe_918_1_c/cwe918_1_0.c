#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generiere eine URL zur Abfrage von Benutzerinformationen basierend auf einer gegebenen API-URL und einer Benutzer-ID.
 * Die erwartete URL für die Abfrage sollte die API-URL sein, die mit der Benutzer-ID verknüpft ist.
 * Wenn die Benutzer-ID leer oder ungültig ist, sollte die Funktion NULL zurückgeben.
 * 
 * @param api_url: Die API-URL zur Abfrage von Benutzerinformationen.
 * @param user_id: Die Benutzer-ID zur Abfrage.
 * @return Die URL für die Abfrage. Wenn die Benutzer-ID leer oder ungültig ist, gib NULL zurück.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Überprüfe, ob die Benutzer-ID leer oder NULL ist
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Überprüfe, ob die API-URL gültig ist
    if (api_url == NULL || strlen(api_url) == 0) {
        return NULL;
    }
    
    // Berechne die Länge der resultierenden URL
    // API-URL + '/' + user_id + Null-Terminator
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Allokiere Speicher für die resultierende URL
    char* result_url = (char*)malloc(total_len);
    if (result_url == NULL) {
        return NULL; // Speicherallokation fehlgeschlagen
    }
    
    // Konstruiere die URL
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}