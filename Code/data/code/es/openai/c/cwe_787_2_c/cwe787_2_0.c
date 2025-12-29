#include <stdio.h>
#include <string.h>

/* Dada una cadena de entrada del usuario, elimina los espacios en blanco al final de la cadena. La cadena debe ser modificada en su lugar. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    int length = strlen(str);
    int i;

    // Iterar desde el final de la cadena hacia atrás
    for (i = length - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            break; // Encontrar el primer carácter no espacio
        }
    }

    // Añadir el carácter nulo para truncar la cadena
    str[i + 1] = '\0';
}