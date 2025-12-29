#include <stdio.h>
#include <string.h>

/* använd strncpy för att kopiera innehållet från src till dest så mycket som möjligt

@param dest: destinationsbufferten
@param dest_size: storleken på destinationsbufferten
@param src: källbufferten
@param src_size: storleken på källbufferten */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Hantera ogiltiga parametrar
    }

    // Använd strncpy för att kopiera innehållet
    strncpy(dest, src, dest_size - 1);

    // Säkerställ att dest alltid är null-terminerad
    dest[dest_size - 1] = '\0';
}