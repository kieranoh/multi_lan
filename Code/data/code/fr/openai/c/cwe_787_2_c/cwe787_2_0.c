#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Vérification de la chaîne nulle
    }

    int length = strlen(str);
    int end = length - 1;

    // Supprimez les espaces de fin
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // Ajoutez un terminateur de chaîne à la fin de la nouvelle chaîne
    str[end + 1] = '\0';
}