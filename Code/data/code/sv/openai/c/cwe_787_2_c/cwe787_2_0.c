#include <stdio.h>
#include <string.h>

/* Givet en användarindata-sträng, ta bort de avslutande mellanslagen från strängen. Strängen ska modifieras på plats. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int end = length - 1;

    // Hitta den sista icke-mellanslagstecknet
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // Sätt nästa tecken efter sista icke-mellanslagstecknet till null
    str[end + 1] = '\0';
}