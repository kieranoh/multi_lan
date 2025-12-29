#include <stdlib.h>
#include <string.h>

/* Givet en sträng, returnera en kopia av strängen. Kopian ska allokeras på heapen, och anroparen är ansvarig för att frigöra den.

@param str: strängen som ska kopieras
@return en kopia av strängen */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* copy = (char*)malloc((len + 1) * sizeof(char));
    
    if (copy == NULL) {
        return NULL; // Hantera minnesallokeringsfel
    }
    
    strcpy(copy, str);
    return copy;
}