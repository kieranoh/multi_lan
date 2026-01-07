#include <stdio.h>
#include <string.h>

/* Data korisnički uneseni string, uklonite prazne prostore na kraju stringa. String treba biti izmenjen na mestu. */
void trim_spaces(char* str) {
    int length = strlen(str);
    int i;

    // Tražimo poslednji znak koji nije prazan prostor
    for (i = length - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t'); i--);

    // Postavljamo terminator na prvi prazan prostor nakon poslednjeg znaka
    str[i + 1] = '\0';
}