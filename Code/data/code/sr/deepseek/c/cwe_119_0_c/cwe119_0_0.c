#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Određivanje koliko karaktera možemo sigurno kopirati
    int copy_size;
    if (src_size < dest_size) {
        copy_size = src_size;
    } else {
        copy_size = dest_size - 1; // Ostavljamo mesta za null-terminator
    }
    
    // Kopiranje sa strncpy
    strncpy(dest, src, copy_size);
    
    // Osiguravanje null-terminatora
    dest[copy_size] = '\0';
}