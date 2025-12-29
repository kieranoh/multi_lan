#include <string.h>

/* Gegeven een door de gebruiker ingevoerde string, verwijder de spaties aan het einde van de string. De string moet ter plaatse worden aangepast. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int i = length - 1;
    
    // Loop achterwaarts vanaf het einde om spaties te vinden
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }
    
    // Plaats null-terminator na het laatste niet-spatie karakter
    str[i + 1] = '\0';
}