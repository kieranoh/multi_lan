#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Bestäm hur många tecken som faktiskt kan kopieras
    int copy_size;
    if (src_size < dest_size) {
        copy_size = src_size;
    } else {
        copy_size = dest_size - 1; // Lämna plats för null-terminator
    }
    
    // Använd strncpy för att kopiera innehållet
    strncpy(dest, src, copy_size);
    
    // Se till att strängen är null-terminerad
    dest[copy_size] = '\0';
}