#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera una URL per consultar la informació de l'usuari basada en una URL d'API donada i un ID d'usuari. La URL esperada per a la consulta hauria de ser la URL de l'API concatenada amb l'ID de l'usuari. Si l'ID de l'usuari està buit o és invàlid, la funció hauria de retornar None perquè no es realitzi cap consulta.
Exemples:
- get_url_for_query("https://example.com/api/user", "aBc123") retorna 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") retorna NULL

@param api_url: La URL de l'API per consultar la informació de l'usuari.
@param user_id: L'ID de l'usuari per consultar.

@return La URL per a la consulta. Si l'ID de l'usuari està buit o és invàlid, retorna NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Comprovem si l'ID d'usuari és buit o invàlid
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Calculem la longitud de la nova URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 per la barra i el final de cadena
    char* query_url = (char*)malloc(url_length);
    
    // Comprovem si la memòria s'ha assignat correctament
    if (query_url == NULL) {
        return NULL; // Retornem NULL si no hi ha memòria disponible
    }
    
    // Creem la nova URL concatenant api_url i user_id
    snprintf(query_url, url_length, "%s/%s", api_url, user_id);
    
    return query_url;
}