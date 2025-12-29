#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Oblicz maksymalną liczbę znaków do skopiowania
    int max_copy = dest_size - 1;  // Zostaw miejsce na null-terminator
    
    if (src_size >= 0) {
        // Jeśli podano src_size, użyj mniejszej wartości
        if (src_size < max_copy) {
            max_copy = src_size;
        }
    } else {
        // Jeśli src_size jest ujemne, traktuj src jako null-terminated string
        strncpy(dest, src, max_copy);
        dest[max_copy] = '\0';
        return;
    }
    
    // Skopiuj znaki
    strncpy(dest, src, max_copy);
    dest[max_copy] = '\0';  // Zawsze null-terminate
}