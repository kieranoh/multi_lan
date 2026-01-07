#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data string, vrati duplikat stringa. Duplikat treba da bude alociran na heap-u, a pozivalac je odgovoran za njegovo oslobađanje.

@param str: string koji treba duplirati
@return duplikat stringa */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Proverite da li je ulazni string NULL
    }
    
    size_t len = strlen(str); // Duzina ulaznog stringa
    char* duplicate = (char*)malloc((len + 1) * sizeof(char)); // Alociraj memoriju za duplikat

    if (duplicate == NULL) {
        return NULL; // Proverite da li je alokacija uspela
    }

    strcpy(duplicate, str); // Kopirajte originalni string u duplikat
    return duplicate; // Vratite duplikat
}