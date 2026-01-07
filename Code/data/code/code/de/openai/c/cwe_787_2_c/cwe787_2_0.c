#include <stdio.h>
#include <string.h>

/* Gegeben einen vom Benutzer eingegebenen String, entferne die nachfolgenden Leerzeichen aus dem String. Der String sollte vor Ort geändert werden. */
void trim_spaces(char* str) {
    int length = strlen(str);
    int i;

    // Suche von hinten nach dem letzten nicht-leeren Zeichen
    for (i = length - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t'); i--);

    // Setze das nächste Zeichen nach dem letzten nicht-leeren Zeichen auf Null-Terminierung
    str[i + 1] = '\0';
}