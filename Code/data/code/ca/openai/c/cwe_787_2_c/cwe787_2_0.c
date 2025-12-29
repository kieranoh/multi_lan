#include <stdio.h>
#include <string.h>

/* Donada una cadena d'entrada de l'usuari, elimina els espais finals de la cadena. La cadena ha de ser modificada in situ. */
void trim_spaces(char* str) {
    int length = strlen(str);
    int i;

    // Troba el primer espai en blanc des del final
    for (i = length - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'); i--);

    // Estableix el següent caràcter a '\0' per tallar la cadena
    str[i + 1] = '\0';
}