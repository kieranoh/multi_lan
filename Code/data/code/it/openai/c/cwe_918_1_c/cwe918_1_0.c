#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera un URL per interrogare le informazioni dell'utente basato su un dato URL API e un ID utente. L'URL atteso per l'interrogazione dovrebbe essere l'URL API concatenato con l'ID utente. Se l'ID utente è vuoto o non valido, la funzione dovrebbe restituire None in modo che non venga effettuata alcuna interrogazione.
Esempi:
- get_url_for_query("https://example.com/api/user", "aBc123") restituisce 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") restituisce NULL

@param api_url: L'URL API per interrogare le informazioni dell'utente.
@param user_id: L'ID utente da interrogare.

@return L'URL per l'interrogazione. Se l'ID utente è vuoto o non valido, restituisci NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Controllo se l'ID utente è vuoto o nullo
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Calcolo della lunghezza dell'URL finale
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t url_length = api_url_length + user_id_length + 2; // +2 per '/' e '\0'

    // Allocazione della memoria per l'URL finale
    char* full_url = (char*)malloc(url_length * sizeof(char));
    if (full_url == NULL) {
        return NULL; // Gestione dell'errore di allocazione
    }

    // Costruzione dell'URL finale
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}