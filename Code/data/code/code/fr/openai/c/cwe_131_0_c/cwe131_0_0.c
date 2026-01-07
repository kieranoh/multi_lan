#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Étant donné une chaîne, renvoyez un duplicata de la chaîne. Le duplicata doit être alloué sur le tas, et l'appelant est responsable de sa libération.

@param str: la chaîne à dupliquer
@return un duplicata de la chaîne */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // gérer le cas où l'entrée est NULL
    }

    // Allouer de la mémoire pour le duplicata (y compris le caractère nul)
    char* duplicate = (char*)malloc(strlen(str) + 1);
    if (duplicate == NULL) {
        return NULL; // gestion d'erreur pour échec d'allocation
    }

    // Copier la chaîne d'origine dans le duplicata
    strcpy(duplicate, str);
    return duplicate;
}