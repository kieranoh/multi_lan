#include <string.h>
#include <ctype.h>

/* Étant donné une chaîne saisie par l'utilisateur, supprimez les espaces de fin de la chaîne. La chaîne doit être modifiée sur place. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Trouver le dernier caractère non-espace
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Terminer la chaîne après le dernier caractère non-espace
    str[i + 1] = '\0';
}