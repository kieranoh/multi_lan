#include <string.h>

/* Gegeben einen vom Benutzer eingegebenen String, entferne die nachfolgenden Leerzeichen aus dem String. Der String sollte vor Ort geändert werden. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Finde den letzten Index, der kein Leerzeichen ist
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }
    
    // Setze das Null-Terminator-Zeichen nach dem letzten nicht-Leerzeichen
    str[i + 1] = '\0';
}