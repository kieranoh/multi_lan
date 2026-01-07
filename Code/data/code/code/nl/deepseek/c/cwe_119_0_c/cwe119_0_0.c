#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Bepaal hoeveel karakters we kunnen kopiëren
    int copy_size;
    if (src_size < dest_size) {
        // Als src_size kleiner is dan dest_size, kopieer alle karakters van src
        copy_size = src_size;
    } else {
        // Als src_size groter is dan of gelijk aan dest_size, kopieer dest_size-1 karakters
        // om ruimte te laten voor de null-terminator
        copy_size = dest_size - 1;
    }
    
    // Gebruik strncpy om de karakters te kopiëren
    strncpy(dest, src, copy_size);
    
    // Zorg ervoor dat de string null-terminated is
    dest[copy_size] = '\0';
}