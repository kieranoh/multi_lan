#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Verificar si el user_id es NULL o vacío
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // Verificar si el user_id contiene solo caracteres válidos (letras, números, guiones bajos)
    // Podemos considerar que un user_id válido debe tener al menos un carácter alfanumérico
    int has_valid_char = 0;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (isalnum((unsigned char)user_id[i])) {
            has_valid_char = 1;
            break;
        }
    }
    
    if (!has_valid_char) {
        return NULL;
    }
    
    // Calcular la longitud necesaria para la nueva cadena
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Asignar memoria para la nueva cadena
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // Fallo en la asignación de memoria
    }
    
    // Construir la cadena resultante
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}