#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data una stringa, restituisci un duplicato della stringa. Il duplicato deve essere allocato nel heap, e il chiamante è responsabile per liberarlo.

@param str: la stringa da duplicare
@return un duplicato della stringa */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Gestione del caso in cui la stringa è NULL
    }

    size_t length = strlen(str); // Calcola la lunghezza della stringa
    char* dup = (char*)malloc((length + 1) * sizeof(char)); // Alloca memoria per il duplicato

    if (dup == NULL) {
        return NULL; // Gestione dell'errore di allocazione
    }

    strcpy(dup, str); // Copia la stringa nel duplicato
    return dup; // Ritorna il duplicato
}