#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Controleer op NULL-pointer
    }

    size_t len = strlen(str);
    
    // Start van het einde van de string en zoek naar niet-spatie karakters
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        len--; // Verklein de lengte totdat er geen spaties meer zijn
    }
    
    str[len] = '\0'; // Voeg null-terminator toe op de nieuwe lengte
}