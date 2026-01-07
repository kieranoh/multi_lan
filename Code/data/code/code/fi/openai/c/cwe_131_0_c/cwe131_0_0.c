#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Anna merkkijono, palauta merkkijonon kopio. Kopio tulisi varata pinolle, ja kutsujan vastuulla on vapauttaa se.

@param str: kopioitava merkkijono
@return kopio merkkijonosta */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Tarkista, että syöte ei ole NULL
    }
    
    size_t len = strlen(str); // Laske merkkijonon pituus
    char* copy = (char*)malloc(len + 1); // Varaa muisti kopiole
    if (copy == NULL) {
        return NULL; // Tarkista, että muistinvaraus onnistui
    }

    strcpy(copy, str); // Kopioi merkkijono
    return copy; // Palauta kopio
}