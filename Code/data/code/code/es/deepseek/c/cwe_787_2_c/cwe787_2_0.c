#include <string.h>
#include <ctype.h>

/* Dada una cadena de entrada del usuario, elimina los espacios en blanco al final de la cadena. La cadena debe ser modificada en su lugar. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int i = length - 1;
    
    // Encontrar el último carácter que no es espacio en blanco
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Colocar el carácter nulo después del último carácter no espacio
    str[i + 1] = '\0';
}