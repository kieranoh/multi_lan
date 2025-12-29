#include <stdlib.h>
#include <string.h>

/* Dada una cadena, devuelve un duplicado de la cadena. El duplicado debe ser asignado en el heap, y el llamador es responsable de liberarlo.

@param str: la cadena a duplicar
@return un duplicado de la cadena */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t length = strlen(str);
    char* duplicate = (char*)malloc(length + 1); // +1 para el carácter nulo

    if (duplicate == NULL) {
        return NULL; // Fallo en la asignación de memoria
    }

    strcpy(duplicate, str); // Copia la cadena original al duplicado
    return duplicate; // Devuelve el puntero al duplicado
}