#include <stdlib.h>
#include <string.h>

/* Gegeven een string, retourneer een duplicaat van de string. Het duplicaat moet op de heap worden toegewezen, en de aanroeper is verantwoordelijk voor het vrijgeven ervan.

@param str: de te dupliceren string
@return een duplicaat van de string */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* duplicate = (char*)malloc(len + 1); // +1 voor de null-terminator
    if (duplicate == NULL) {
        return NULL; // Fout bij geheugenallocatie
    }
    
    strcpy(duplicate, str);
    return duplicate;
}