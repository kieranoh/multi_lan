#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return; // Verifica se la stringa è NULL

    int length = strlen(str);
    int end = length - 1;

    // Trova l'ultimo carattere non spazio
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // Aggiungi il terminatore di stringa dopo l'ultimo carattere non spazio
    str[end + 1] = '\0';
}