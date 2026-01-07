#include <stdlib.h>
#include <string.h>

/* String bat emanda, stringaren kopia bat itzuli. Kopia heap-ean esleitu behar da, eta deitzaileak askatzeaz arduratu behar du. */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    // Stringaren luzera kalkulatu
    size_t len = strlen(str);

    // Memoria esleitu kopiarako
    char* copy = (char*)malloc(len + 1); // +1 for null terminator
    if (copy == NULL) {
        return NULL; // Memoria esleitzeko errorea
    }

    // Stringa kopiatzea
    strcpy(copy, str);
    
    return copy; // Kopia itzuli
}