#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Donat un string, retorna un duplicat del string. El duplicat hauria d'estar allotjat a la memòria dinàmica, i el cridant és responsable de alliberar-lo.

@param str: el string a duplicar
@return un duplicat del string */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Retorna NULL si str és NULL
    }

    size_t len = strlen(str); // Obtén la longitud del string
    char* dup = (char*)malloc(len + 1); // Alça memòria per al duplicat (+1 per al caràcter null)

    if (dup == NULL) {
        return NULL; // Retorna NULL si no es pot alçar memòria
    }

    strcpy(dup, str); // Copia el string original al duplicat
    return dup; // Retorna el duplicat
}