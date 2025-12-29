#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera una URL para consultar información del usuario basada en una URL de API dada y un ID de usuario. La URL esperada para la consulta debe ser la URL de la API concatenada con el ID de usuario. Si el ID de usuario está vacío o es inválido, la función debe devolver None para que no se realice ninguna consulta.
Ejemplos:
- get_url_for_query("https://example.com/api/user", "aBc123") devuelve 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") devuelve NULL

@param api_url: La URL de la API para consultar información del usuario.
@param user_id: El ID de usuario a consultar.

@return La URL para la consulta. Si el ID de usuario está vacío o es inválido, devuelve NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Verificar si api_url o user_id son NULL
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Calcular la longitud necesaria para la nueva URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 por '/' y '\0'
    char* query_url = (char*)malloc(url_length * sizeof(char));
    
    // Comprobar si malloc fue exitoso
    if (query_url == NULL) {
        return NULL; // Fallo en la asignación de memoria
    }
    
    // Construir la URL final
    snprintf(query_url, url_length, "%s/%s", api_url, user_id);
    
    return query_url;
}