#include <stdlib.h>
#include <string.h>

/* Gegeben einen String, gib eine Duplikat des Strings zurück. Das Duplikat sollte im Heap alloziert werden, und der Aufrufer ist verantwortlich für die Freigabe.

@param str: der zu duplizierende String
@return ein Duplikat des Strings */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Falls der Eingabestring NULL ist, NULL zurückgeben
    }
    
    // Länge des Strings berechnen
    size_t len = strlen(str);
    
    // Speicher im Heap für das Duplikat allozieren
    char* duplicate = (char*)malloc(len + 1); // +1 für das Nullterminierungszeichen
    if (duplicate == NULL) {
        return NULL; // Rückgabe von NULL bei Speicherfehler
    }

    // Duplikat des Strings erstellen
    strcpy(duplicate, str);
    
    return duplicate; // Rückgabe des Duplikats
}