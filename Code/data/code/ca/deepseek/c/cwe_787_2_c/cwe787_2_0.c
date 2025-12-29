#include <string.h>
#include <ctype.h>

/* Donada una cadena d'entrada de l'usuari, elimina els espais finals de la cadena. La cadena ha de ser modificada in situ. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Troba l'últim caràcter que no és un espai
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Col·loca el caràcter nul al final de la cadena sense espais
    str[i + 1] = '\0';
}