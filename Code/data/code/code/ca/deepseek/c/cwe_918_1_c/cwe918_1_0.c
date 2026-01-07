#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Verificar si user_id es NULL o buit
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Verificar si user_id és vàlid (almenys un caràcter vàlid)
    int valid = 0;
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!iscntrl(user_id[i])) {  // Comprovar que no sigui un caràcter de control
            valid = 1;
            break;
        }
    }
    
    if (!valid) {
        return NULL;
    }
    
    // Calcular la longitud necessària per a la nova cadena
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Reservar memòria per a la nova cadena
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL;  // Error en l'assignació de memòria
    }
    
    // Construir la URL resultant
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}