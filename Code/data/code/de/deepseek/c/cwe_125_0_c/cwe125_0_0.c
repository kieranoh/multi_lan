#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Prüfe auf NULL-Pointer
    if (prices == NULL || index_str == NULL) {
        return -1;
    }
    
    // Prüfe auf leeren String
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Validiere, dass der String nur Ziffern enthält
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Konvertiere String zu Integer
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Prüfe auf Konvertierungsfehler
    if (*endptr != '\0') {
        return -1;
    }
    
    // Prüfe auf Überlauf (wenn der String zu groß für long war)
    if (index == LONG_MAX || index == LONG_MIN) {
        return -1;
    }
    
    // Prüfe, ob der Index im gültigen Bereich liegt
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Gib den Preis am angegebenen Index zurück
    return prices[index];
}