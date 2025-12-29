#include <stdlib.h>
#include <string.h>

/* Zadani niz, vrati duplikat niza. Duplikat treba biti alociran na hrpi, a pozivatelj je odgovoran za njegovo oslobađanje.

@param str: niz za duplikaciju
@return duplikat niza */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char* duplicate = (char*)malloc(len + 1); // +1 for the null terminator

    if (duplicate == NULL) {
        return NULL; // Memory allocation failed
    }

    strcpy(duplicate, str);
    return duplicate;
}