#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Određujemo koliko znakova možemo kopirati
    int copy_size;
    if (src_size < dest_size) {
        copy_size = src_size;
    } else {
        copy_size = dest_size - 1; // Ostavljamo prostor za null terminator
    }
    
    // Kopiramo sadržaj koristeći strncpy
    strncpy(dest, src, copy_size);
    
    // Osiguravamo da je string null-terminiran
    dest[copy_size] = '\0';
}